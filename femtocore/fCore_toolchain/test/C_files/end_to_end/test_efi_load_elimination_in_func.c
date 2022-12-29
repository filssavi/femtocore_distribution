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


float sin(float theta){
    float efi_in[2];

    efi_in[0] = 0;
    efi_in[1] = theta;

    float sin_theta = efi(efi_in, 2);
    sin_theta = itf(sin_theta);
    sin_theta = 0.000030518*sin_theta;

    return sin_theta;
}

float cos(float theta){

    float efi_in[2];

    efi_in[0] = 1;
    efi_in[1] = theta;

    float cos_theta = efi(efi_in, 2);
    return cos_theta;
}


int main(){
    float theta;

    float s_th = sin(theta);
    float c_th = cos(theta);

}


