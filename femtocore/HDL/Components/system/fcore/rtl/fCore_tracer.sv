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
`include "interfaces.svh"

module fCore_tracer #(
    parameter PC_WIDTH = 12,
    MAX_CHANNELS = 255
)(
    input wire clock,
    input wire reset,
    input wire start,
    input wire done,
    axi_stream.slave instruction_stream,
    axi_stream.slave operand_a,
    axi_stream.slave operand_b,
    axi_stream.slave operand_c,
    axi_stream.slave operation,
    axi_stream.slave result,
    axi_stream.master efi_arguments,
    axi_stream.slave efi_results,
    axi_stream.slave efi_writeback,
    axi_stream.slave dma_write
);


    wire [(PC_WIDTH + $clog2(MAX_CHANNELS) )-1:0] cur_address;
    assign cur_address = {instruction_stream.dest[$clog2(MAX_CHANNELS)-1:0], instruction_stream.user[PC_WIDTH-1:0]};
    reg [(PC_WIDTH + $clog2(MAX_CHANNELS) )-1:0] prev_address;

    enum logic [1:0] { 
        tracer_idle = 0, 
        tracer_running = 1,
        tracer_wait_efi = 2
    } tracer_fsm = tracer_idle;

    int pipe_fd;

    string state, cast_tmp;

    initial begin
        pipe_fd = $fopen("/tmp/fCore_tracer_fifo", "w");
    end


    always_ff @(posedge clock)begin
        if(!reset)begin
            tracer_fsm <= tracer_idle;
            state = "";
        end else begin

            state = "";
            prev_address <= cur_address;

            if(cur_address != prev_address) begin
                if(tracer_fsm==tracer_running)begin
                    state = {state, "||"};

                    cast_tmp.hextoa(cur_address);
                    state = {state, cast_tmp, "|"};

                    cast_tmp.hextoa(instruction_stream.data);
                    state = {state, cast_tmp, "|"};

                    // operand A
                    
                    cast_tmp.hextoa(operand_a.data);
                    state = {state, cast_tmp, "|"};

                    cast_tmp.hextoa(operand_a.dest);
                    state = {state, cast_tmp, "|"};

                    cast_tmp.hextoa(operand_a.user);
                    state = {state, cast_tmp, "|"};

                    // operand B

                    cast_tmp.hextoa(operand_b.data);
                    state = {state, cast_tmp, "|"};

                    cast_tmp.hextoa(operand_b.dest);
                    state = {state, cast_tmp, "|"};

                    cast_tmp.hextoa(operand_b.user);
                    state = {state, cast_tmp, "|"};

                    // operand C

                    cast_tmp.hextoa(operand_c.data);
                    state = {state, cast_tmp, "|"};

                    cast_tmp.hextoa(operand_c.dest);
                    state = {state, cast_tmp, "|"};

                    cast_tmp.hextoa(operand_c.user);
                    state = {state, cast_tmp, "|"};

                    // operation

                    cast_tmp.hextoa(operation.data);
                    state = {state, cast_tmp, "|"};
                    
                    // result

                    cast_tmp.hextoa(result.data);
                    state = {state, cast_tmp, "|"};

                    cast_tmp.hextoa(result.dest);
                    state = {state, cast_tmp, "|"};

                    // efi_arguments
                    
                    cast_tmp.hextoa(efi_arguments.data);
                    state = {state, cast_tmp, "|"};

                    cast_tmp.hextoa(efi_arguments.dest);
                    state = {state, cast_tmp, "|"};

                    // efi_results
 
                    cast_tmp.hextoa(efi_results.data);
                    state = {state, cast_tmp, "|"};

                    cast_tmp.hextoa(efi_results.dest);
                    state = {state, cast_tmp, "|"};
 
                    // efi_writeback
 
                    cast_tmp.hextoa(efi_writeback.data);
                    state = {state, cast_tmp, "|"};

                    cast_tmp.hextoa(efi_writeback.dest);
                    state = {state, cast_tmp, "|"};

                    state = {state, "||"};
                    
                    $fwrite(pipe_fd, state);
                end
            end


            case (tracer_fsm)
                tracer_idle:begin
                    if(start)begin
                        $fwrite(pipe_fd, "---start_round---");
                        tracer_fsm <= tracer_running;
                    end
                end
                tracer_running:begin
                    if(done)begin
                        $fwrite(pipe_fd, "---finish_round---");
                        tracer_fsm <= tracer_idle;
                    end
                end
            endcase

            if(tracer_fsm == tracer_idle)begin
                if(dma_write.valid)begin

                    $fwrite(pipe_fd, "---start_dma---");
                    state = "||";
                    cast_tmp.hextoa(dma_write.data);
                    state = {state, cast_tmp, "|"};

                    cast_tmp.hextoa(dma_write.dest);
                    state = {state, cast_tmp, "|"};
                    state = {state,"||"};
                    $fwrite(pipe_fd, state);
                    $fwrite(pipe_fd, "---end_dma---");
                end
            end


        end
    end


endmodule
