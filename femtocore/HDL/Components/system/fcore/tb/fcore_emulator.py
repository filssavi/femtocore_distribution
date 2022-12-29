#!/usr/bin/env python3
import argparse
import os
import sys
import numpy as np
import struct

def parse_arguments():
    parser = argparse.ArgumentParser(description='Emulator for the fcore architecture')
    parser.add_argument('FILE', type=str, help='input program')
    parser.add_argument('--o',  type=str, help='output register dump')
    parser.add_argument('--c', type=str, help='simulation register dump to validate')

    args = parser.parse_args()
     
    

    if args.c is not None:
        check_file = os.path.abspath(args.c)
    else:
        check_file = None

    if args.o is not None:
        output_file = os.path.abspath(args.o)
    else:
        output_file = None

    input_file = ''

    if os.path.exists(os.path.join(os.getcwd(), args.FILE)):
        input_file = os.path.abspath(os.path.join(os.getcwd(), args.FILE))
    else:
        print(os.path.join(os.getcwd(), args.FILE))
        print(f'ERROR: No inputfile has been specified')
        exit(1)

    return input_file, output_file, check_file


def main():
    input_file, output_file, check_file = parse_arguments()

    with open(input_file) as f:
        program = f.readlines()
    registers = [0]*16

    idx = 0

    while idx < len(program):
        instruction = int(program[idx].lstrip(), 16)
        opcode = instruction & 0x1f
        reg_arg_1 = ((instruction & 0x1E0) >> 5)
        reg_arg_2 = ((instruction & 0x1E00) >> 9)
        reg_arg_3 = ((instruction & 0x1E000) >> 13)
        immediate_load = (instruction & 0x1ffE00) >> 9
        branch_target = (instruction & 0x1ffE000) >> 13
        
        if opcode == 0:
            pass
        elif opcode == 1:
            registers[reg_arg_3] = registers[reg_arg_1] + registers[reg_arg_2]
        elif opcode == 2:
            registers[reg_arg_3] = registers[reg_arg_1] - registers[reg_arg_2]
        elif opcode == 3:
            registers[reg_arg_3] = registers[reg_arg_1] * registers[reg_arg_2]
        elif opcode == 4:
            registers[reg_arg_2] = float(registers[reg_arg_1])
        elif opcode == 5:
            registers[reg_arg_2] = int(registers[reg_arg_1])
        elif opcode == 6:
            if reg_arg_1 != 0:
                registers[reg_arg_1] = program[idx+1]
            idx = idx+1
        elif opcode == 7:
            if reg_arg_1 != 0:
                registers[reg_arg_1] = immediate_load
        elif opcode == 8:
            if registers[reg_arg_1] > registers[reg_arg_2]:
                idx += branch_target
        elif opcode == 9:
            if registers[reg_arg_1] <= registers[reg_arg_2]:
                idx += branch_target
        elif opcode == 10:
            if registers[reg_arg_1] == registers[reg_arg_2]:
                idx += branch_target
        elif opcode == 11:
            if registers[reg_arg_1] != registers[reg_arg_2]:
                idx += branch_target
        elif opcode == 12:
            idx = len(program)+1
            break
        idx += 1

    if output_file:
        with open(output_file) as f:
            for i in registers:
                f.write(f'{i}\n')

    if check_file:
        with open(check_file) as f:
            raw_content = f.readlines()
        
        check_registers = [int(x.lstrip()) for x in raw_content]
        if check_registers != registers[1:16]:
            print("HARDWARE REGISTERS")
            print(check_registers)
            print("EMULATOR REGISTERS")
            print(registers[1:16])
            print("ERROR: The emulated register set does not match the input one")
            exit(2)


if __name__ == "__main__":
    main()
    exit(0)
