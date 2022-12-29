`timescale 10 ns / 1 ns

module axil_skid_buffer_tb();
    
    logic clk, rst;

    //clock generation
    initial clk = 0; 
    always #0.5 clk = ~clk;


    reg producer_valid, consumer_ready;
    wire producer_ready, consumer_valid;
    reg [31:0] producer_data;
    wire [31:0] consumer_data;

    axil_skid_buffer #(
        .REGISTER_OUTPUT(1),
        .DATA_WIDTH(32)
    ) DUT (
        .clock(clk),
        .reset(rst),
        .in_valid(producer_valid),
        .in_ready(producer_ready),
        .in_data(producer_data),
        .out_valid(consumer_valid),
        .out_ready(consumer_ready),
        .out_data(consumer_data)
    );
    

    // reset generation
    initial begin
        producer_data <= 'hCAFECABE;;
        producer_valid <= 0;
        consumer_ready <= 0;
        #3.5 rst<=0;
        #5 rst <=1;

        // NO BACKPRESSURE
        #10;
        consumer_ready <= 1;
        producer_valid <= 1;
        #1 producer_valid <= 0;
        #1 consumer_ready <= 0;
        
        // WITH BACKPRESSURE
        #10
        producer_data <= 'hDEADCAFE;
        #90;
        producer_valid <= 1;
        #3 consumer_ready <= 1;
        #1 consumer_ready <= 0;
        #1 producer_valid <= 0;

        #2 consumer_ready <= 1;
        #4 consumer_ready <= 0;
    end

    reg [2:0] input_transactions_count = 0;
    reg [31:0]input_data [1:0] = {0,0};

    always @(posedge clk) begin : input_transactions_counter
        if(rst)begin
            @(posedge producer_valid & producer_ready) input_transactions_count <= input_transactions_count+1;
        end else begin
            input_transactions_count <= 0;
        end
        if(producer_valid & producer_ready) input_data[input_transactions_count] <= producer_data;
    end

    always @(negedge clk) begin 
        if(producer_valid & producer_ready) input_data[input_transactions_count] <= producer_data;
    end

    reg [2:0] output_transactions_count = 0;
    reg [31:0]output_data [1:0] = {0,0};

    always @(posedge clk) begin : output_transactions_counter
        if(rst)begin
            @(posedge consumer_valid & consumer_ready) output_transactions_count <= output_transactions_count+1;
        end else begin
            output_transactions_count <= 0;
        end        
        if(consumer_valid & consumer_ready) output_data[output_transactions_count] <= consumer_data;
    end


    always @(negedge clk) begin 
        if(consumer_valid & consumer_ready) output_data[output_transactions_count] <= consumer_data;
    end


    initial begin
        wait(output_transactions_count == 2 && input_transactions_count == 2);
        wait(consumer_ready);
        wait(producer_ready);
        if((output_data[0][31:0] != input_data[0][31:0]) || (output_data[1][31:0] != input_data[1][31:0])) begin
            $error("SIMULATION FAILED");
            $finish();
        end else begin
            $display("SIMULATION SUCCESSFUL");
            $finish();
        end
    end

endmodule