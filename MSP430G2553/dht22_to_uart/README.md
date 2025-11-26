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

## How Data is Stored in dht22data Union

The data is stored bit-by-bit in the `DHT_IN_BIT_HIGH` state of the interrupt handler:

```c
case DHT_IN_BIT_HIGH:
    // Shift left to make room for new bit
    dht_data.bytes[dht_data_byte] <<= 1;

    // If pulse is long (>750 ticks at 16MHz ≈ 47us), it's a '1' bit
    if (TA1CCR0 > 750)
    {
        dht_data.bytes[dht_data_byte] |= 1;  // Set bit to 1
    }
    // Otherwise it stays 0 (short pulse ≈ 27us)

    // Move to next bit
    if (++dht_data_bit >= 8)
    {
        dht_data_bit = 0;      // Reset bit counter
        dht_data_byte++;        // Move to next byte
    }
```

1. Initialization (line 121):

```c
dht_data_byte = dht_data_bit = 0;  // Start at byte 0, bit 0
```

2. For each bit received (40 bits total):

- Shift left: Make room for new bit
- Check pulse width:
  - Long pulse (>47us) → bit = 1
  - Short pulse (<47us) → bit = 0
- Store bit: OR with 1 if needed
- Increment counters: Move to next bit/byte

3. Data fills the union:

```c
dht_data.bytes[0] = hh  // Humidity high
dht_data.bytes[1] = hl  // Humidity low
dht_data.bytes[2] = th  // Temperature high
dht_data.bytes[3] = tl  // Temperature low
dht_data.bytes[4] = crc // Checksum
```

Because `dht22data` is a union, you can access the same memory two ways:

```c
// Access as array
dht_data.bytes[0]  // First byte

// Access as struct (same memory!)
dht_data.val.hh    // First byte (humidity high)
```
