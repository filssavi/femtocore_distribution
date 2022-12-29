# Sicdrive-HDL

This projects aims at implementing a versatile high speed control for power electronics based on Xilinx Zynq system on chip

## Prerequisites

The only prerequisite software is the Vivado environement for FPGA developement available for [free download](https://www.xilinx.com/products/design-tools/vivado.html)

## Getting Started


The each module can be found in its own directory in the *Components* folder, moreover complex blocks are broken down in multiple sub-modules.
Each (sub)module has a common structure with the *rtl* directory containing the synthetizable source files and while the *tb* folder contains simulation sources.

To build the Vivado project for a (sub)module the make.tcl file has to be run within the vivado Tcl shell as follows.

```
    cd /path/to/module/directory
    source make.tcl
```

 A project folder will be created with the same name as the (sub)module. This is ignored by the git VCS, as it's content is purely local. For any modification to the configurations to be permanent it has to be added to the make TCL script.

 If any compatibly licensed third party module or library is used the required License file/notice should be placed in the *Library Licenses* folder. The original License and copyright informations should also be retained at the top of the source files themselves.

## Contributing

Every new contributor should place his details in the CREDITS file the license notice found in the project files should be retained. When editing a file for the first time the name of the contributor should be added to the copyright notice.

## Modules breakdown

* **ADC INTERFACE:** This module implements a versatile ADC interface that can perform filtering, linearization on incoming samples, with pre and post filtering fault tripping possibility
* **PWM GENERATOR:** Highly flexible PWM generator with two phase shiftable 32 bit timers each one feeding 6 gatable pwm channels with automatic dead-time insertion.
* **SPI:** Fully fledged SPI peripheral.
*  **TRANSFORM ACCELLERATION UNIT:** This module implements Clarke and park transforms. sine and cosine functions are based on a 512 word l6 bit look up table. A 0.17° overall resolution is obtained by storing only a quarter of the sinusoid period in the LUT and using trigonometric identities to reconstruct the whole period


## Authors

* **Filippo Savi** - *sole contributor* - filippo.savi@nottingham.edu.cn

See also the list of [contributors](CREDITS) who participated in this project.

## License

This project is licensed under the Apache 2.0 License - see the [LICENSE.txt](LICENSE.txt) file for details
