cmake_minimum_required(VERSION 3.10)
project(msp430 VERSION 1.0)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR msp430)

set(TOOLCHAIN_PREFIX "/usr/msp430-elf")
set(CMAKE_C_COMPILER "${TOOLCHAIN_PREFIX}/bin/msp430-elf-gcc")
set(CMAKE_ASM_COMPILER "${TOOLCHAIN_PREFIX}/bin/msp430-elf-gcc")
set(CMAKE_OBJCOPY "${TOOLCHAIN_PREFIX}/bin/msp430-elf-objcopy")
set(CMAKE_SIZE "${TOOLCHAIN_PREFIX}/bin/msp430-elf-size")

add_subdirectory(MSP430G2553)
