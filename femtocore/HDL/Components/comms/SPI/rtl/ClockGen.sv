// Copyright 2021 University of Nottingham Ningbo China
// Author: Filippo Savi <filssavi@gmail.com>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
`timescale 10 ns / 1 ns

module ClockGen (
    input wire       clockIn,
    input wire       reset,
    input wire       enable,
    input wire [2:0] dividerSetting,
    input wire       polarity,
    output wire      sync,
    output reg       timebaseOut
);

    reg internal_sync;
    reg [6:0] timebases=7'b0;
    reg [1:0] count4=2'b0;
    reg [2:0] count8=3'b0;
    reg [3:0] count16=4'b0;
    reg [4:0] count32=5'b0;

    reg justEnabled = 1'b0;
    reg running = 1'b0;
    reg int_timebase;

    assign timebaseOut = polarity ? ~int_timebase : int_timebase;
    always @(posedge clockIn) begin
        // Clock/2 generation
        timebases[1] <= ~timebases[1];
        //update counters
        count4 <= count4 + 1'b1;
        count8 <= count8 + 1'b1;
        count16 <= count16 + 1'b1;
        count32 <= count32 + 1'b1;
         case (dividerSetting)
            0: internal_sync <= 1; 
            1: internal_sync <= ~timebases[1];
            2: internal_sync <= count4==0;
            3: internal_sync <= count8==0;
            4: internal_sync <= count16==0;
            5: internal_sync <= count32==0;
            default:internal_sync <= 1;
        endcase
    end

    assign sync = internal_sync;

    always@(*) begin
		timebases[0]<=clockIn;
        // Clock/4 generation
        if (count4==1 | count4==2) begin
            timebases[2]<=1'b1;
        end else begin
            timebases[2]<=1'b0;
        end
        // Clock/8 generation
        if (count8>=1 & count8<=4) begin
            timebases[3]<=1'b1;
        end else begin
            timebases[3]<=1'b0;
        end
        // Clock/16 generation
        if (count16>=1 & count16<=9) begin
            timebases[4]<=1'b1;
        end else begin
            timebases[4]<=1'b0;
        end
        // Clock/32 generation
        if (count32>=1 & count32<=17) begin
            timebases[5]<=1'b1;
        end else begin
            timebases[5]<=1'b0;
        end
    end
    
    always @(posedge clockIn) begin
        if(enable & ~running) begin
            justEnabled <= 1'b1;
        end else begin
            justEnabled <= 1'b0;
        end
    end

    // Declare state register
    reg		[1:0]state;

    // Declare states
    parameter S0 = 0, S1 = 1, S2 = 2;

    // Determine the next state synchronously, based on the
    // current state and the input
    always @ (posedge clockIn or negedge reset) begin
        if (~reset) begin
            state <= S0;
        end else begin
            case (state)
                S0: if (justEnabled & ~timebases[dividerSetting]) begin
                        state <= S1;
                    end else begin
                        state <= S0;
                    end
                S1: if (running & enable) begin
                        state <= S1;
                    end else begin
                        state <= S2;
                    end
                S2: if (~enable) begin
                        state <= S0;
                    end else begin
                        state <= S2;
                    end
                default:  state <= S0;
            endcase
        end 
    end

  
    always @ (*) begin
        if(~reset) begin
            int_timebase <=1'b0;
            running <= 1'b0;
        end else begin
            case (state)
                S0: if (justEnabled & ~timebases[dividerSetting]) begin
                        running <= 1'b1;
                        int_timebase <= timebases[dividerSetting];
                    end else begin
                        int_timebase <= 1'b0;
						running <= 1'b0;
                    end
                S1: if(running & enable) begin
						running <= 1'b1;
                        int_timebase <= timebases[dividerSetting];
                    end else begin
						running <= 1'b1;
                        int_timebase <= 1'b0;
                    end
                S2: if (~enable) begin
                        running <=1'b0;
                        int_timebase <= 1'b0;
                    end else begin
					    running <=1'b0;
                        int_timebase <= 1'b0;
                    end
                default:begin
                    running <=1'b0;
                    int_timebase <= 1'b0;
                end
            endcase
        end
    end

endmodule