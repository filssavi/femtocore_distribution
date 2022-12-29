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
`timescale 1 ns / 100 ps

	module DMA_manager_inst #
	(
		parameter integer C_M_AXI_ADDR_WIDTH	= 32,
		parameter integer C_M_AXI_DATA_WIDTH	= 32
	)(
		input wire [31:0] data,
		input wire [31:0] address,
		input wire  INIT_AXI_TXN,
		output reg  ERROR,
		output wire  TXN_DONE,

		input wire  M_AXI_ACLK,
		input wire  M_AXI_ARESETN,
		output wire [C_M_AXI_ADDR_WIDTH-1 : 0] M_AXI_AWADDR,
		output wire  M_AXI_AWVALID,
		input wire  M_AXI_AWREADY,
		output wire [C_M_AXI_DATA_WIDTH-1 : 0] M_AXI_WDATA,
		output wire  M_AXI_WVALID,
		input wire  M_AXI_WREADY,
		input wire [1 : 0] M_AXI_BRESP,
		input wire  M_AXI_BVALID,
		output wire  M_AXI_BREADY,
		output wire [C_M_AXI_ADDR_WIDTH-1 : 0] M_AXI_ARADDR,
		output wire  M_AXI_ARVALID,
		input wire  M_AXI_ARREADY,
		input wire [C_M_AXI_DATA_WIDTH-1 : 0] M_AXI_RDATA,
		input wire [1 : 0] M_AXI_RRESP,
		input wire  M_AXI_RVALID,
		output wire  M_AXI_RREADY
	);

	localparam [1:0] IDLE = 2'b00, INIT_WRITE   = 2'b01;
	reg [1:0] mst_exec_state;




	// AXI4LITE signals
	//write address valid
	reg  	axi_awvalid;
	//write data valid
	reg  	axi_wvalid;
	//read address valid
	reg  	axi_arvalid;
	//read data acceptance
	reg  	axi_rready;
	//write response acceptance
	reg  	axi_bready;
	//A pulse to initiate a write transaction
	reg  	start_single_write;
	//A pulse to initiate a read transaction
	reg  	write_issued;
	//Asserts when a single beat read transaction is issued and remains asserted till the completion of read trasaction.
	reg  	writes_done;
	//Flag is asserted when the write index reaches the last write transction number
	reg  	last_write;

	reg [31:0] axi_awaddr;
	reg [31:0] axi_wdata;
	
	// I/O Connections assignments

	//Adding the offset address to the base addr of the slave
	assign M_AXI_AWADDR	= axi_awaddr;
	//AXI 4 write data
	assign M_AXI_WDATA	= axi_wdata;
	assign M_AXI_AWVALID	= axi_awvalid;
	//Write Data(W)
	assign M_AXI_WVALID	= axi_wvalid;
	//Write Response (B)
	assign M_AXI_BREADY	= axi_bready;
	//Read Address (AR)
	assign M_AXI_ARADDR	= 0;
	assign M_AXI_ARVALID	= axi_arvalid;
	//Read and Read Response (R)
	assign M_AXI_RREADY	= axi_rready;
	//Example design I/O
	assign TXN_DONE	= writes_done;



	always @(posedge M_AXI_ACLK) begin   
		if (M_AXI_ARESETN == 0) begin
				axi_awvalid <= 1'b0;
				axi_awaddr <= 32'b0;     
		end else begin
			if (start_single_write) begin                  
				axi_awvalid <= 1'b1; 
				axi_awaddr <= address;
			end else if (M_AXI_AWREADY && axi_awvalid) begin                  
				axi_awvalid <= 1'b0; 
			end                    
		end 
	end     

	always @(posedge M_AXI_ACLK) begin    
		if (M_AXI_ARESETN == 0 ) begin
			axi_wvalid <= 1'b0;
			axi_wdata <= 0;
		end else if (start_single_write) begin          
			axi_wvalid <= 1'b1;
			axi_wdata <= data;
		end else if (M_AXI_WREADY && axi_wvalid) begin    
			axi_wvalid <= 1'b0;        
		end  
	end      

	always @(posedge M_AXI_ACLK) begin                  
	    if (M_AXI_ARESETN == 0) begin              
	        axi_bready <= 1'b0;                     
	    end else if (M_AXI_BVALID && ~axi_bready) begin  
	        axi_bready <= 1'b1;                     
	    end else if (axi_bready) begin              
		    axi_bready <= 1'b0;                     
	    end else          
	      	axi_bready <= axi_bready;                 
	  end                    
	  



	always @(posedge M_AXI_ACLK) begin       
	    if (M_AXI_ARESETN == 0) begin   
	    	axi_arvalid <= 1'b0;     
			axi_rready <= 1'b0;    
	    end   
	end         



	
	//--------------------------------
	//User Logic
	//--------------------------------
	  
	//implement master command interface state machine  
	always @ ( posedge M_AXI_ACLK) begin        
		if (M_AXI_ARESETN == 1'b0) begin    
			// reset condition              
			// All the signals are assigned default values under reset condition          
			mst_exec_state  <= IDLE;                     
			start_single_write <= 1'b0;   
			write_issued  <= 1'b0;             
			ERROR <= 1'b0;
		end else begin    
			// state transition            
			case (mst_exec_state)         	
				IDLE:               
					if (INIT_AXI_TXN) begin                   
						mst_exec_state  <= INIT_WRITE;    
						start_single_write <= 0;           
						ERROR <= 1'b0;
					end else
						begin                   
						mst_exec_state  <= IDLE;             
					end                     
					
				INIT_WRITE:                 
					// This state is responsible to issue start_single_write pulse to       
					// initiate a write transaction. Write transactions will be             
					// issued until last_write signal is asserted.   
					// write controller       
					if (writes_done) begin                   
						mst_exec_state <= IDLE;//               
					end else begin                   
						mst_exec_state  <= INIT_WRITE;               
						if (~axi_awvalid && ~axi_wvalid && ~M_AXI_BVALID && ~last_write && ~start_single_write && ~write_issued) begin             
							start_single_write <= 1'b1;            
							write_issued  <= 1'b1;                 
						end else if (axi_bready) begin             
							write_issued  <= 1'b0;                 
						end else begin             
							start_single_write <= 1'b0; //Negate to generate a pulse      
						end               
					end    

				default: begin                    
					mst_exec_state  <= IDLE;              
				end
			endcase
		end        
	end
	               
	  //Terminal write count              
	               
	always @(posedge M_AXI_ACLK) begin        
		if (M_AXI_ARESETN == 0 | mst_exec_state==IDLE)           
		last_write <= 1'b0;           
		else if (M_AXI_AWREADY)                
		last_write <= 1'b1;             
		else       
		last_write <= last_write;       
	end          
	               
	//Check for last write completion.  
																					
	//This logic is to qualify the last write count with the final write              
	//response. This demonstrates how to confirm that a write has been                
	//committed. 
																					
	always @(posedge M_AXI_ACLK) begin        
		if (M_AXI_ARESETN == 0)           
			writes_done <= 1'b0;													
			//The writes_done should be associated with a bready response                 
		else if (last_write && M_AXI_BVALID && axi_bready)       
			writes_done <= 1'b1;            
		else if (mst_exec_state==IDLE)
			writes_done <=0;
		else       
			writes_done <= writes_done;     
	end     
																					

	endmodule
