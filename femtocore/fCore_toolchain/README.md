# fCore Toolchain

[![CircleCI](https://circleci.com/gh/filssavi/fCore_toolchain.svg?style=shield&circle-token=1145a78e36553f20bf503af95f607591199be482)](https://app.circleci.com/pipelines/github/filssavi/fCore_toolchain)


The fCore toolchain is a set of tools that allow the compilation of various source languages to executable femtoCore machine instructions.

- fCore_has is a tool that can be used to translate assembly language sources to object code. To simplify software development few features typical of high level languages are supported, like loops (automatically unrolled to serial code) and named variables.

- fCore_cc is a compiler that translated a subset of the C language to femtoCore object code.


## Features

### assembler

- For loops (implemented through simple unrolling)
- Named Variables
- Floating point literals

### C compiler

- All hardware supported C language operators
- Intrinsic functions exposing advanced fCore features
- looping support (unrollable loops only)
- compile time conditionals
- Input and outputs register pinning for DMA I/O

**planned features:**

- limited branchless programming support for run time conditional execution

**Unsupported features:**

- postfix increment/decrement
- Pointers
- Non inline function calls
- while loops
- do-while loops
- goto statements
- structures, unions and enums
- typedefs

It should be noted that these features will never be supported as they are either completely incompatible with the femtoCore hardware/ISA or not necessary for the intended use of the processor, that should never be used as a general purpose CPU, a role for which it is not designed.


## Platforms

#### Officially supported

- Ubuntu 20.04+

#### Known to work

- Linux (any distribution)

#### Unsupported

- Windows
- mac OS
- WSL

## Building from source

To build the software from sources run the following steps:

```bash
    mkdir build && cd build
    cmake ..
    cmake --build .
    sudo cmake --install
```
    
## Dependencies

The following libraries are required to build and run the software:

- antlr-cpp-runtime 4.9
