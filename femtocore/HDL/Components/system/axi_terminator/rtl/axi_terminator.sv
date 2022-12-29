
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
`include "interfaces.svh"


module axi_terminator (
    input wire        clock,
    input wire        reset,
    AXI.slave  axi
);


    reg axi_awv_awr_flag;
    reg axi_arv_arr_flag; 




    assign axi.BID = axi.AWID;
    assign axi.RID = axi.ARID;
  
    always @( posedge clock ) begin : axi_awready_generation
        if ( reset == 1'b0 ) begin
            axi.AWREADY <= 1'b0;
            axi_awv_awr_flag <= 1'b0;
        end else begin    
            if (~axi.AWREADY && axi.AWVALID && ~axi_awv_awr_flag && ~axi_arv_arr_flag) begin
                axi.AWREADY <= 1'b1;
                axi_awv_awr_flag  <= 1'b1; 
            end else if (axi.WLAST && axi.WREADY) begin
                axi_awv_awr_flag  <= 1'b0;
            end else begin
                axi.AWREADY <= 1'b0;
            end
        end 
    end     


    always @( posedge clock ) begin : wready_generation
        if ( reset == 1'b0 ) begin
            axi.WREADY <= 1'b0;
        end else begin    
            if ( ~axi.WREADY && axi.WVALID && axi_awv_awr_flag) begin
                axi.WREADY <= 1'b1;
            end else if (axi.WLAST && axi.WREADY) begin
                axi.WREADY <= 1'b0;
            end
        end 
    end       
    
    always @( posedge clock ) begin : write_response_generation
        if ( reset == 1'b0 ) begin
            axi.BVALID <= 0;
            axi.BRESP <= 2'b0;
            axi.BUSER <= 0;
        end else begin    
            if (axi_awv_awr_flag && axi.WREADY && axi.WVALID && ~axi.BVALID && axi.WLAST ) begin
                axi.BVALID <= 1'b1;
                axi.BRESP  <= 2'b0; 
            end else begin
                if (axi.BREADY && axi.BVALID) begin
                    axi.BVALID <= 1'b0; 
                end  
            end
        end
    end   


    always @( posedge clock ) begin : read_address_ready_generation
        if ( reset == 1'b0 ) begin
            axi.ARREADY <= 1'b0;
            axi_arv_arr_flag <= 1'b0;
        end else begin    
            if (~axi.ARREADY && axi.ARVALID && ~axi_awv_awr_flag && ~axi_arv_arr_flag) begin
                axi.ARREADY <= 1'b1;
                axi_arv_arr_flag <= 1'b1;
            end else if (axi.RVALID && axi.RREADY) begin
                axi_arv_arr_flag  <= 1'b0;
            end else begin
                axi.ARREADY <= 1'b0;
            end
        end 
    end       
    
    always @( posedge clock ) begin : read_address_valid_gen
        if ( reset == 1'b0 ) begin
          axi.RVALID <= 0;
          axi.RRESP  <= 0;
        end else begin    
            if (axi_arv_arr_flag && ~axi.RVALID) begin
              axi.RVALID <= 1'b1;
              axi.RRESP  <= 2'b0; 
            end else if (axi.RVALID && axi.RREADY) begin
              axi.RVALID <= 1'b0;
            end            
        end
    end    
    

endmodule