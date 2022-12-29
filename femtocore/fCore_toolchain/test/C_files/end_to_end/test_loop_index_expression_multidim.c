// Copyright 2022 Filippo Savi <filssavi@gmail.com>
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
//

int main(){

    float v_cells[5][4];
    float v_arms[2] = {0.0, 0.0};


    v_arms[1] = 0.0; // THESE ARE NOT WORKING WHEN THE LOOP IS USED

    for(int i = 0; i<2; ++i){
        int idx_l = 2+i;
        v_arms[1] += v_cells[idx_l][1];
    }
}

