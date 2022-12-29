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

grammar asm_grammar;

program : code;
code : ( instruction |for_block | pragma |declaration)+;

declaration : (input_decl | variable_decl | constant_decl | output_decl);

instruction : reg_instr | imm_instr | indep_instr | pseudo_instr | branch_instr | conv_instr | load_instr;

reg_instr : reg_opcode  operand ',' operand ',' destination;
imm_instr : imm_opcode destination ',' immediate;
load_instr: 'ldc' destination ',' (FloatingPointLiteral | integer_const);
branch_instr : branch_opcode operand ',' operand ',' operand;
conv_instr : conv_opcode operand ',' operand;
indep_instr : 'stop' | 'nop';

pseudo_instr : pseudo_opcode operand ',' operand  (',' operand)*;

operand : Register | Identifier;


destination: Register | Identifier;
immediate : Integer | Hexnum | Octalnum | Identifier;

float_const : FloatingPointLiteral;
integer_const: Integer | Hexnum | Octalnum;

reg_opcode : 'add' | 'sub' | 'mul' | 'and' | 'or' | 'satp' | 'satn' | 'efi' | 'bset' | 'bsel' | 'xor';
conv_opcode: 'itf' | 'fti' | 'not' | 'rec' | 'abs'| 'popcnt';
imm_opcode : 'ldr';
branch_opcode: 'ble' | 'bgt' | 'beq' | 'bne';

pseudo_opcode: 'mov';


for_block: 'for('for_decl';'for_end';'(for_incr|for_dec)')' '{'code'}';
for_incr: Identifier ('++');
for_dec: Identifier ('--');
for_decl: Identifier '=' Integer;

for_end: Identifier for_end_comp_type Integer;
for_end_comp_type : ('<' | '>' | '<=' | '>=');
pragma: '#pragma ' Identifier;


variable_decl : 'let' (Register | Identifier);
constant_decl : 'const' (Register | Identifier);
input_decl : 'input' (Register | Identifier);
output_decl : 'output' (Register | Identifier);

Register: 'r' (Digit +);

Identifier
   : Letter ('_' | Letter | Digit)*
   ;
Hexnum
   : '0x' HexDigit +
   ;
Integer
   : (Digit +)
   ;
Octalnum
   : ('0' .. '7') + ('o' | 'O')
   ;
fragment HexDigit
   : ('0' .. '9' | 'a' .. 'f' | 'A' .. 'F')
   ;
FloatingPointLiteral
   : '-'? ('0' .. '9') + '.' ('0' .. '9')* Exponent? | '.' ('0' .. '9') + Exponent? | ('0' .. '9') + Exponent
   ;
fragment Exponent
   : ('e' | 'E') ('+' | '-')? ('0' .. '9') +
   ;
String
   : ' \'' ('\\' . | ~ ('\\' | '\''))* '\''
   ;
fragment Letter
   : ('a' .. 'z' | 'A' .. 'Z')
   ;
fragment Digit
   : '0' .. '9'
   ;

Label
   : Identifier (':')
   ;
WS
   : (' ' | '\t' | '\n' | '\r') -> skip
   ;

BlockComment
    :   '/*' .*? '*/'
        -> skip
    ;

LineComment
    :   '//' ~[\r\n]*
        -> skip
    ;