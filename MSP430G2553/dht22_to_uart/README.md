# DHT22 + msp430

This project reads temperature and humidity from a DHT22 sensor and outputs the data via UART.

## Hardware

- MSP430G2553 microcontroller
- DHT22 sensor connected to P2.0
- UART TX connected to serial adapter (e.g., USB-to-TTL converter) on P1.2

## Features

- Reads DHT22 sensor data every 2 seconds
- Outputs temperature (Celsius) and humidity (%) via UART
- Includes error handling for sensor timeouts
- UART baud rate: 9600
