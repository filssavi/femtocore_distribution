`timescale 10 ns / 1 ns
`include "interfaces.svh"

module axis_skid_buffer_tb();
    
    logic clk, rst;

    //clock generation
    initial clk = 0; 
    always #0.5 clk = ~clk;

    axi_stream producer();
    axi_stream consumer();

    axis_skid_buffer #(
        .REGISTER_OUTPUT(1),
        .DATA_WIDTH(32)
    ) DUT (
        .clock(clk),
        .reset(rst),
        .axis_in(producer),
        .axis_out(consumer)
    );
    

    // reset generation
    initial begin
        producer.data <= 'hCAFECABE;;
        producer.valid <= 0;
        consumer.ready <= 0;
        #3.5 rst<=0;
        #5 rst <=1;

        // NO BACKPRESSURE
        #10;
        consumer.ready <= 1;
        producer.valid <= 1;
        #1 producer.valid <= 0;
        #1 consumer.ready <= 0;
        
        // WITH BACKPRESSURE
        #10
        producer.data <= 'hDEADCAFE;
        #90;
        producer.valid <= 1;
        #3 consumer.ready <= 1;
        #1 consumer.ready <= 0;
        #1 producer.valid <= 0;

        #2 consumer.ready <= 1;
        #4 consumer.ready <= 0;
    end

    reg [2:0] input_transactions_count = 0;
    reg [31:0]input_data [1:0] = {0,0};

    always @(posedge clk) begin : input_transactions_counter
        if(rst)begin
            @(posedge producer.valid & producer.ready) input_transactions_count <= input_transactions_count+1;
        end else begin
            input_transactions_count <= 0;
        end
        if(producer.valid & producer.ready) input_data[input_transactions_count] <= producer.data;
    end

    always @(negedge clk) begin 
        if(producer.valid & producer.ready) input_data[input_transactions_count] <= producer.data;
    end

    reg [2:0] output_transactions_count = 0;
    reg [31:0]output_data [1:0] = {0,0};

    always @(posedge clk) begin : output_transactions_counter
        if(rst)begin
            @(posedge consumer.valid & consumer.ready) output_transactions_count <= output_transactions_count+1;
        end else begin
            output_transactions_count <= 0;
        end        
        if(consumer.valid & consumer.ready) output_data[output_transactions_count] <= consumer.data;
    end


    always @(negedge clk) begin 
        if(consumer.valid & consumer.ready) output_data[output_transactions_count] <= consumer.data;
    end


    initial begin
        wait(output_transactions_count == 2 && input_transactions_count == 2);
        wait(consumer.ready);
        wait(producer.ready);
        if((output_data[0][31:0] != input_data[0][31:0]) || (output_data[1][31:0] != input_data[1][31:0])) begin
            $error("SIMULATION FAILED");
            $finish();
        end else begin
            $display("SIMULATION SUCCESSFUL");
            $finish();
        end
    end

endmodule