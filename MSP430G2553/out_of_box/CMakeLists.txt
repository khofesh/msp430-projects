# MSP430G2553 Out Of Box Experience Project
set(MCU "msp430g2553")
set(PROJECT_NAME "out_of_box_g2553")

# Source files
set(SOURCES
    main.c
)

# Create executable
add_executable(${PROJECT_NAME}.elf ${SOURCES})

# MCU-specific compiler flags
target_compile_options(${PROJECT_NAME}.elf PRIVATE
    -mmcu=${MCU}
    ${COMMON_FLAGS}
    -Os  # Optimize for size
)

# MCU-specific linker flags
target_link_options(${PROJECT_NAME}.elf PRIVATE
    -mmcu=${MCU}
    -T${MSP430_LIB_DIR}/${MCU}.ld
    ${COMMON_LINKER_FLAGS}
)

# Include directories
target_include_directories(${PROJECT_NAME}.elf PRIVATE
    ${MSP430_INCLUDE_DIR}
)

# Generate hex file
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex ${PROJECT_NAME}.elf ${PROJECT_NAME}.hex
    COMMENT "Generating HEX file: ${PROJECT_NAME}.hex"
)

# Generate binary file
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin
    COMMENT "Generating BIN file: ${PROJECT_NAME}.bin"
)

# Print size information
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_SIZE} --format=berkeley ${PROJECT_NAME}.elf
    COMMENT "Size information:"
)
