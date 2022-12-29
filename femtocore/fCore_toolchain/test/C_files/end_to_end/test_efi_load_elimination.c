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
// limitations under the License.02/07/2021.
//


int main(){
    float theta;

    float s_th;
    float c_th;


    float trig_in[2];

    trig_in[1] = theta;
    trig_in[0] = 0;
    s_th = efi(trig_in, 2);
    s_th = 0.000030518*s_th;
    trig_in[0] = 1;
    c_th = efi(trig_in, 2);


}
