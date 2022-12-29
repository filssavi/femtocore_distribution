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

float add_first(float mem_1[2][2][3], float mem_2[7], int i){
    return mem_1[0][0][i] + mem_2[i];
}


int main(){
    int a[2][2][3] = {
            {
                {0.0, 1.0, 2.0}, {3.0, 4.0, 5.0}
            },
            {
                {6.0, 7.0, 8.0}, {9.0, 10.0, 11.0}
            }
    };
    int b[7] = {2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0};


    float c = add_first(a, b, 1);
}
