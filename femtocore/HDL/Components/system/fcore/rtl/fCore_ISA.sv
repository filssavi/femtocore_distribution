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

package fcore_isa;
    parameter NOP = 0;
    parameter ADD = 1;
    parameter SUB = 2;
    parameter MUL = 3; 
    parameter ITF = 4;
    parameter FTI = 5;
    parameter LDC = 6;
    parameter LDR = 7;
    parameter BGT = 8;
    parameter BLE = 9;
    parameter BEQ = 10;
    parameter BNE = 11;
    parameter STOP = 12;
    parameter LAND = 13;
    parameter LOR = 14;
    parameter LNOT = 15;
    parameter SATP = 16;
    parameter SATN = 17;
    parameter REC = 18;
    parameter POPCNT = 19;
    parameter ABS = 20;
    parameter EFI = 21;
    parameter BSET = 22;
    parameter BSEL = 25;
    parameter LXOR = 26;
endpackage

typedef enum logic [4:0] { 
    NOP = fcore_isa::NOP,
    ADD = fcore_isa::ADD,
    SUB = fcore_isa::SUB,
    MUL = fcore_isa::MUL,
    ITF = fcore_isa::ITF,
    FTI = fcore_isa::FTI,
    LDC = fcore_isa::LDC,
    LDR = fcore_isa::LDR,
    BGT = fcore_isa::BGT,
    BLE = fcore_isa::BLE,
    BEQ = fcore_isa::BEQ,
    BNE = fcore_isa::BNE,
    STOP = fcore_isa::STOP,
    LAND = fcore_isa::LAND,
    LOR = fcore_isa::LOR,
    LNOT = fcore_isa::LNOT,
    SATP = fcore_isa::SATP,
    SATN = fcore_isa::SATN,
    REC = fcore_isa::REC,
    POPCNT = fcore_isa::POPCNT,
    ABS = fcore_isa::ABS,
    EFI = fcore_isa::EFI,
    BSET = fcore_isa::BSET,
    BSEL = fcore_isa::BSEL,
    LXOR = fcore_isa::LXOR,
    RESERVED_0 = 27,
    RESERVED_1 = 28,
    RESERVED_2 = 29,
    RESERVED_3 = 30,
    RESERVED_4 = 31
 } fcore_operations;