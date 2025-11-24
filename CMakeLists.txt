cmake_minimum_required(VERSION 3.10)

# Set system and processor before project()
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR msp430)

# Toolchain configuration
set(TOOLCHAIN_PREFIX "/usr/msp430-elf")
set(CMAKE_C_COMPILER "${TOOLCHAIN_PREFIX}/bin/msp430-elf-gcc")
set(CMAKE_ASM_COMPILER "${TOOLCHAIN_PREFIX}/bin/msp430-elf-gcc")
set(CMAKE_OBJCOPY "${TOOLCHAIN_PREFIX}/bin/msp430-elf-objcopy")
set(CMAKE_SIZE "${TOOLCHAIN_PREFIX}/bin/msp430-elf-size")

# Prevent CMake from testing the compiler
set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)

project(msp430-projects C ASM)

# Common MSP430 settings
set(MSP430_INCLUDE_DIR "${TOOLCHAIN_PREFIX}/msp430-elf/include")
set(MSP430_LIB_DIR "${TOOLCHAIN_PREFIX}/msp430-elf/lib")

# Common compiler flags for all MSP430 targets
set(COMMON_FLAGS "-Wall" "-Wextra" "-ffunction-sections" "-fdata-sections")
set(COMMON_LINKER_FLAGS "-Wl,--gc-sections")

add_subdirectory(MSP430G2553)
add_subdirectory(MSP430FR2355)
