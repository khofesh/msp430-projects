/*
license: https://github.com/rbasoalto/msp430-dht22

The MIT License (MIT)

Copyright (c) 2014 Rodrigo Basoalto
*/
#pragma once

#include <stdint.h>
// explain the data structure: humidity high, humidity low, temperature high, temperature low, CRC
typedef union {
  struct {
    uint8_t hh;
    uint8_t hl;
    uint8_t th;
    uint8_t tl;
    uint8_t crc;
  } val;
  uint8_t bytes[5];
} dht22data;

void dht_start_read();
int dht_get_temp();
int dht_get_rh();
uint8_t dht_is_crc_valid();
