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

module antiPark (
    input  wire clock,
    input  wire reset,
    input  wire signed [15:0] theta,
    input  wire signed [17:0] d,
    input  wire signed [17:0] q,
    output reg signed [17:0] alpha,
    output reg signed [17:0] beta
);

    wire results_ready;
    wire signed [15:0] tableSinOut;
    wire signed [15:0] tableCosOut;
    wire signed [17:0] extendedTableSinOut;
    wire signed [17:0] extendedTableCosOut;
    reg signed  [35:0] internal_alpha = 0;
    reg signed  [35:0] internal_beta = 0;

    assign extendedTableSinOut = tableSinOut<<<2;
    assign extendedTableCosOut = tableCosOut<<<2;

    trigonometricUnit parkSinTable(
        .clk(clock),
        .theta(theta),
        .sin_theta(tableSinOut),
        .cos_theta(tableCosOut),
        .output_valid(results_ready)
    );

    always @(posedge clock) begin
        if(~reset) begin
            internal_alpha <= 0;
            internal_beta <= 0;
        end else begin
            if(results_ready) begin
                internal_alpha <= (extendedTableCosOut*d) - (extendedTableSinOut*q);
                internal_beta <=  (extendedTableSinOut*d) + (extendedTableCosOut*q);
                alpha <= internal_alpha >>> 17;
                beta <= internal_beta >>> 17;
            end
        end
    end

endmodule