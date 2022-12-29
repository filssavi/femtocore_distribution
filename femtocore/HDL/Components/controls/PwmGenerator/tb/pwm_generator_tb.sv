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

`timescale 10ns / 1ns
`include "axis_BFM.svh"
`include "interfaces.svh"

module pwm_generator_tb();

    reg  clk, reset;
    reg ext_tb=0;
    wire [11:0] pwm;
    
    parameter SB_TIMEBASE_ADDR = 'h43C00000;
    parameter SB_CHAIN_1_ADDR  = 'h43C00100;
    parameter SB_CHAIN_2_ADDR  = 'h43C00200;


    axi_lite axil();

    axis_BFM write_BFM;
    axis_BFM read_req_BFM;
    axis_BFM read_resp_BFM;

    axi_stream read_req();
    axi_stream read_resp();
    axi_stream write();

    axis_to_axil WRITER(
        .clock(clk),
        .reset(reset), 
        .axis_write(write),
        .axis_read_request(read_req),
        .axis_read_response(read_resp),
        .axi_out(axil)
    );
    
    PwmGenerator UUT (
        .clock(clk),
        .reset(reset),
        .ext_timebase(ext_tb),
        .axi_in(axil),
        .fault(0),
        .pwm_out(pwm) 
    );

    always #3 ext_tb = ~ext_tb; 

    //clock generation
    initial clk = 0; 
    always #0.5 clk = ~clk; 

    realtime period_result = 0;
    integer duty_result = 0;
    integer deadtime_result = 0;
    integer phase_shift_result = 0;

    integer counter_low = 'h1;
    integer counter_high = 'h45;
    integer compare_low = 'h4;
    integer compare_high = 'h20;
    integer deadtime_setting = 'h8;
    integer phase_shift_setting = 'h100;


    reg output_test_complete = 0;
    reg online_duty_test_complete = 0;
    reg deadtime_test_complete = 0;
    reg phase_shift_test_complete = 0;
    reg sync_test_complete = 0;

    initial begin

        write_BFM = new(write,2.5);
        read_req_BFM = new(read_req, 2.5);
        read_resp_BFM = new(read_resp, 2.5);

        //Initial status
        reset <=1'h1;
        #1 reset <=1'h0;
        //TESTS
        #5.5 reset <=1'h1;

        #4 start_output_test();
        output_test_check(period_result,duty_result);
        output_test_complete = 1;
        
        #100 compare_low <= 'h5;
        compare_high <= 'h22;

        #1 start_online_duty_change_test();
        online_duty_change_test_check(duty_result);
        online_duty_test_complete = 1;
        
        //Test dead time insertion
        #100 start_deadtime_test();
        deadtime_test_check(deadtime_result);
        deadtime_test_complete = 1;

        #100 start_phase_shift_test();
        phase_shift_test_check(phase_shift_result);
        phase_shift_test_complete = 1;

        #100 start_sync_test();
        sync_test_check();
        sync_test_complete = 1;
        #300 $display("SIMULATION COMPLETED SUCCESSFULLY");
        $finish();
    end

    task output_test_check(output realtime period, integer duty);
        real expected_period;
        integer expected_duty;
        realtime first_edge = 0, second_edge =0, third_edge=0;

        @(posedge pwm[0]);
            first_edge = $realtime;
        @(negedge pwm[0]);
            second_edge = $realtime;
        @(posedge pwm[0]);
            third_edge = $realtime;
        
        expected_period = ((counter_high-counter_low)*2+2)*10;
        period = (third_edge-first_edge)*10;
        assert (expected_period == period) else begin
            $fatal(2,"FAILED output period test: the expected period was %e the measured one was %e ", expected_period, period);
        end

        expected_duty = ((compare_high-compare_low)*2+2)/(period/10)*100;
        duty  = $rtoi((second_edge-first_edge)/period*1000);
        assert (expected_duty == duty) else begin
            $fatal(2,"FAILED output duty cycle test: the expected duty cycle was %e the measured one was %e ", expected_duty, duty);
        end
    endtask
    
    task online_duty_change_test_check(output integer duty);
        integer expected_duty;
        realtime first_edge = 0, second_edge =0;

        @(posedge pwm[0]);
            first_edge = $realtime;
        @(negedge pwm[0]);
            second_edge = $realtime;

        expected_duty = ((compare_high-compare_low)*2+2)/(period_result/10)*100;
        duty  = (second_edge-first_edge)/period_result*1000;
        assert (expected_duty == duty) else begin
            $fatal(2,"FAILED output duty cycle test: the expected duty cycle was %e the measured one was %e ", expected_duty, duty);
        end
    endtask

    task deadtime_test_check(output integer deadtime);
        integer expected_deadtime;
        realtime first_edge = 0, second_edge =0;

        @(negedge pwm[3]);
            first_edge = $realtime;
        @(posedge pwm[0]);
            second_edge = $realtime;
        
        
        expected_deadtime = deadtime_setting;
        deadtime  = (second_edge-first_edge);
        assert (expected_deadtime == deadtime) else begin
            $fatal(2,"FAILED deadtime insertion test: the expected deadtime was %e the measured one was %e ", expected_deadtime, deadtime);
        end
    endtask

    task phase_shift_test_check(output integer phase_shift);
        integer expected_phase_shift;
        realtime first_edge = 0, second_edge =0;

        
        @(posedge pwm[0]);
            first_edge = $realtime;
        @(posedge pwm[6]);
            second_edge = $realtime;
        
        expected_phase_shift = phase_shift_setting+2;
        phase_shift  = (second_edge-first_edge);
        assert (expected_phase_shift == phase_shift) else begin
            $fatal(2,"FAILED carrier phase shift test: the expected phase shift was %e the measured one was %e ", expected_phase_shift, phase_shift);
        end
    endtask

    task sync_test_check();
        integer expected_duration;
        realtime start_time = 0, second_edge =0;
        real duration;
        
        start_time = $realtime;
        @(posedge pwm[0]);
            second_edge = $realtime;     
        
        expected_duration = 71;
        duration  = (second_edge-start_time);
        assert (expected_duration == duration) else begin
            $fatal(2,"FAILED sync test: the expected remaining duration of the current period was %e the measured one was %e ", expected_duration, duration);
        end
    endtask


    task start_output_test();
        #1 write_BFM.write_dest(32'h111100, SB_TIMEBASE_ADDR);
        //Compare low 1
        #1 write_BFM.write_dest(compare_low, SB_CHAIN_1_ADDR+8'h00);
        #1 write_BFM.write_dest(compare_low, SB_CHAIN_1_ADDR+8'h04);
        #1 write_BFM.write_dest(compare_low, SB_CHAIN_1_ADDR+8'h08);
        //Compare high 1
        #1 write_BFM.write_dest(compare_high, SB_CHAIN_1_ADDR+8'h0c);
        #1 write_BFM.write_dest(compare_high, SB_CHAIN_1_ADDR+8'h10);
        #1 write_BFM.write_dest(compare_high, SB_CHAIN_1_ADDR+8'h14);
        //Deadtime
        #1 write_BFM.write_dest(deadtime_setting, SB_CHAIN_1_ADDR+8'h18);
        #1 write_BFM.write_dest(deadtime_setting, SB_CHAIN_1_ADDR+8'h1c);
        #1 write_BFM.write_dest(deadtime_setting, SB_CHAIN_1_ADDR+8'h20);
        //Counter limits
        #1 write_BFM.write_dest(counter_low, SB_CHAIN_1_ADDR+8'h24);
        #1 write_BFM.write_dest(counter_high, SB_CHAIN_1_ADDR+8'h28);
        //Phase Shift
        #1 write_BFM.write_dest(32'h0, SB_CHAIN_1_ADDR+8'h2c);
        //Output Enables
        #1 write_BFM.write_dest(32'h3F, SB_CHAIN_1_ADDR+8'h30);

          //Compare low 2
        #1 write_BFM.write_dest(compare_low, SB_CHAIN_2_ADDR+8'h00);
        #1 write_BFM.write_dest(compare_low, SB_CHAIN_2_ADDR+8'h04);
        #1 write_BFM.write_dest(compare_low, SB_CHAIN_2_ADDR+8'h08);
        //Compare high 2
        #1 write_BFM.write_dest(compare_high, SB_CHAIN_2_ADDR+8'h0c);
        #1 write_BFM.write_dest(compare_high, SB_CHAIN_2_ADDR+8'h10);
        #1 write_BFM.write_dest(compare_high, SB_CHAIN_2_ADDR+8'h14);
        //Deadtime
        #1 write_BFM.write_dest(deadtime_setting, SB_CHAIN_2_ADDR+8'h18);
        #1 write_BFM.write_dest(deadtime_setting, SB_CHAIN_2_ADDR+8'h1c);
        #1 write_BFM.write_dest(deadtime_setting, SB_CHAIN_2_ADDR+8'h20);
        //Counter limits
        #1 write_BFM.write_dest(counter_low, SB_CHAIN_2_ADDR+8'h24);
        #1 write_BFM.write_dest(counter_high, SB_CHAIN_2_ADDR+8'h28);
        //Phase Shift
        #1 write_BFM.write_dest(32'h0, SB_CHAIN_2_ADDR+8'h2c);
        //Output Enables
        #1 write_BFM.write_dest(32'h3F, SB_CHAIN_2_ADDR+8'h30);

        // Counter control 1
        #1 write_BFM.write_dest(32'h0, SB_CHAIN_1_ADDR+8'h38);
        // Counter control 2
        #1 write_BFM.write_dest(32'h0, SB_CHAIN_2_ADDR+8'h38);
        // Timebase settings
        #1 write_BFM.write_dest(32'h111128, SB_TIMEBASE_ADDR);
    endtask

    task start_online_duty_change_test();
        #1 write_BFM.write_dest(compare_low, SB_CHAIN_1_ADDR+8'h00);
        #1 write_BFM.write_dest(compare_low, SB_CHAIN_1_ADDR+8'h04);
        #1 write_BFM.write_dest(compare_low, SB_CHAIN_1_ADDR+8'h08);
        #1 write_BFM.write_dest(compare_high, SB_CHAIN_1_ADDR+8'h0c);
        #1 write_BFM.write_dest(compare_high, SB_CHAIN_1_ADDR+8'h10);
        #1 write_BFM.write_dest(compare_high, SB_CHAIN_1_ADDR+8'h14);
        #1 write_BFM.write_dest(compare_low, SB_CHAIN_2_ADDR+8'h00);
        #1 write_BFM.write_dest(compare_low, SB_CHAIN_2_ADDR+8'h04);
        #1 write_BFM.write_dest(compare_low, SB_CHAIN_2_ADDR+8'h08);
        #1 write_BFM.write_dest(compare_high, SB_CHAIN_2_ADDR+8'h0c);
        #1 write_BFM.write_dest(compare_high, SB_CHAIN_2_ADDR+8'h10);
        #1 write_BFM.write_dest(compare_high, SB_CHAIN_2_ADDR+8'h14);
    endtask

    task start_deadtime_test();
        #1 write_BFM.write_dest(32'h111108, SB_TIMEBASE_ADDR);
        #10 write_BFM.write_dest(32'h3F, SB_CHAIN_1_ADDR+8'h34);
        #1 write_BFM.write_dest(32'h3F, SB_CHAIN_2_ADDR+8'h34);
        #1 write_BFM.write_dest(32'h111128, SB_TIMEBASE_ADDR);
    endtask

    task start_phase_shift_test();
        #1 reset <=1'h0;
        #3 reset <=1'h1;

        //Compare low 1
        write_BFM.write_dest(compare_low, SB_CHAIN_1_ADDR+8'h00);
        write_BFM.write_dest(compare_low, SB_CHAIN_1_ADDR+8'h04);
        write_BFM.write_dest(compare_low, SB_CHAIN_1_ADDR+8'h08);
        //Compare high 1
        write_BFM.write_dest(compare_high, SB_CHAIN_1_ADDR+8'h0C);
        write_BFM.write_dest(compare_high, SB_CHAIN_1_ADDR+8'h10);
        write_BFM.write_dest(compare_high, SB_CHAIN_1_ADDR+8'h14);
        //Deadtime
        write_BFM.write_dest(deadtime_setting, SB_CHAIN_1_ADDR+8'h18);
        write_BFM.write_dest(deadtime_setting, SB_CHAIN_1_ADDR+8'h1c);
        write_BFM.write_dest(deadtime_setting, SB_CHAIN_1_ADDR+8'h20);
        //Counter limits
        write_BFM.write_dest(counter_low, SB_CHAIN_1_ADDR+8'h24);
        write_BFM.write_dest(counter_high, SB_CHAIN_1_ADDR+8'h28);
        //Phase Shift
        write_BFM.write_dest(32'h0, SB_CHAIN_1_ADDR+8'h2c);
        //Output Enables
        write_BFM.write_dest(32'h3F, SB_CHAIN_1_ADDR+8'h30);

        //Compare low 1
        write_BFM.write_dest(compare_low, SB_CHAIN_2_ADDR+8'h00);
        write_BFM.write_dest(compare_low, SB_CHAIN_2_ADDR+8'h04);
        write_BFM.write_dest(compare_low, SB_CHAIN_2_ADDR+8'h08);
        //Compare high 1
        write_BFM.write_dest(compare_high, SB_CHAIN_2_ADDR+8'h0C);
        write_BFM.write_dest(compare_high, SB_CHAIN_2_ADDR+8'h10);
        write_BFM.write_dest(compare_high, SB_CHAIN_2_ADDR+8'h14);
        //Deadtime 2
        write_BFM.write_dest(deadtime_setting, SB_CHAIN_2_ADDR+8'h18);
        write_BFM.write_dest(deadtime_setting, SB_CHAIN_2_ADDR+8'h1c);
        write_BFM.write_dest(deadtime_setting, SB_CHAIN_2_ADDR+8'h20);
        //Counter limits 2  
        write_BFM.write_dest(counter_low, SB_CHAIN_2_ADDR+8'h24);
        write_BFM.write_dest(counter_high, SB_CHAIN_2_ADDR+8'h28);
        //Phase Shift 2
        #100 write_BFM.write_dest(phase_shift_setting, SB_CHAIN_2_ADDR+8'h2c);
        //Output Enables 2
        write_BFM.write_dest(32'h3F, SB_CHAIN_2_ADDR+8'h30);
        // Counter control 1
        write_BFM.write_dest(32'h0, SB_CHAIN_1_ADDR+8'h38);
        // Counter control 2
        write_BFM.write_dest(32'h0, SB_CHAIN_2_ADDR+8'h38);
        write_BFM.write_dest(32'h111128, SB_TIMEBASE_ADDR);

    endtask

    task start_sync_test();
        write_BFM.write_dest(32'h111168, SB_TIMEBASE_ADDR);
        #2 write_BFM.write_dest(32'h111128, SB_TIMEBASE_ADDR);
    endtask

    
endmodule
