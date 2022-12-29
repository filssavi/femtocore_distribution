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
// limitations under the License.07/07/2021.
//
#define MAX_MATRIX 3

void matrix_matrix_add(float mat_1[MAX_MATRIX][MAX_MATRIX], float mat_2[MAX_MATRIX][MAX_MATRIX], float mat_3[MAX_MATRIX][MAX_MATRIX], int M, int N){
    mat_3[1][1] = mat_1[1][1]+ mat_2[0][1];
}

int main(){

    float test_in;
    #pragma input(test_in, r25)

    float a[2][2] = {{1.0, 2.0}, {4.0, 5.0}};
    float b[2][2] = {{1.0, 2.0}, {4.0, 5.0}};
    #pragma output(c, {r12, r13, r14, r15})
    float c[2][2];
    matrix_matrix_add(a, b, c, 2, 2);
    c[1][1] = test_in*c[1][1];
    return 0;
}