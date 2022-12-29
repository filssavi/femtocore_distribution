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


float integrate(float in, float Ts, float memory) {
    float out = memory+Ts*in;

    out = satn(out, -150.0);
    out = satp(out, 150.0);
    return out;
}


int main(){


    int test_in;

    float in_1 = 5.0;

    float integ;

    float test_out = integrate(test_in*in_1, 1e-5, integ);

    return 0;
}
