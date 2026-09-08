/**
 * @file ATTinySerial.cpp
 * @author DampflokHD
 * @brief Ultra-minimalist UART TX library for ATtiny microcontrollers.
 * @version 1.0.0
 * @date 2026-09-08
 * 
 * @copyright Copyright (c) 2026 DampflokHD. Licensed under the MIT License.
 */

#include "ATTinySerial.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay_basic.h>
#include <math.h>


ATTinySerial::ATTinySerial(uint8_t pin) {
    tx_pin = pin;
    delay_cycles = 0;
}

void ATTinySerial::begin(uint32_t baudrate, uint8_t pin) {
    tx_pin = pin;
    begin(baudrate);
}

void ATTinySerial::begin(uint32_t baudrate) {
    delay_cycles = 0;

    if (baudrate == 0 || tx_pin >= 8) return;

    uint32_t cycles = (uint32_t)F_CPU / baudrate / 4;
    if (cycles > 3) cycles -= 3;  // Compensate for the per-bit instruction overhead.
    if (cycles == 0 || cycles > UINT16_MAX) return;

    DDRB |= (1 << tx_pin);  // Set the TX pin as output
    PORTB |= (1 << tx_pin);  // Set selected TX pin high (idle state for UART)

    delay_cycles = (uint16_t)cycles;  // Calculate delay cycles based on CPU frequency and baud rate
}

// Write a single character
void ATTinySerial::write(char c) {
    if (delay_cycles == 0) return;

    volatile uint8_t* port = &PORTB;
    const uint8_t mask = (uint8_t)(1 << tx_pin);
    const uint8_t inverse_mask = (uint8_t)~mask;
    const uint16_t delay = delay_cycles;
    uint8_t value = (uint8_t)c;
    uint8_t sreg = SREG;
    cli();

    // Start bit
    *port &= inverse_mask;
    _delay_loop_2(delay);

    // 8 Data bits
    for (uint8_t i = 8; i > 0; --i) {
        if (value & 0x01) {
            *port |= mask;
        } else {
            *port &= inverse_mask;
        }
        _delay_loop_2(delay);
        value >>= 1;
    }

    // Stop bit
    *port |= mask;

    SREG = sreg;
    _delay_loop_2(delay);
}

void ATTinySerial::print(char c) {
    write(c);
}

void ATTinySerial::print(const char* str) {
    if (str == nullptr) return;

    while (*str) {
        write(*str++);
    }
}

void ATTinySerial::print(const __FlashStringHelper* str) {
    if (str == nullptr) return;

    PGM_P p = reinterpret_cast<PGM_P>(str);
    char c;
    while ((c = pgm_read_byte(p++))) {
        write(c);
    }
}

// Booleans
void ATTinySerial::print(bool b) {
    write(b ? '1' : '0');
}

// Integers
void ATTinySerial::print(int8_t num) {
    print((int32_t)num);
}

void ATTinySerial::print(uint8_t num) {
    print((uint32_t)num);
}

void ATTinySerial::print(int16_t num) {
    print((int32_t)num);
}

void ATTinySerial::print(uint16_t num) {
    print((uint32_t)num);
}

void ATTinySerial::print(int32_t num) {
    if (num == 0) {
        write('0');
        return;
    }
    if (num < 0) {
        write('-');
        print(static_cast<uint32_t>(-(num + 1)) + 1); 
        return;
    }
    print(static_cast<uint32_t>(num));
}

void ATTinySerial::print(uint32_t num) {
    if (num == 0) {
        write('0');
        return;
    }
    char buf[10];
    uint8_t i = 0;
    while (num > 0) {
        buf[i++] = (num % 10) + '0';
        num /= 10;
    }
    while (i > 0) {
        write(buf[--i]);
    }
}

void ATTinySerial::print(float num, uint8_t decimals) {
    if (isnan(num)) {
        print("nan");
        return;
    }
    if (isinf(num)) {
        print(num < 0.0f ? "-inf" : "inf");
        return;
    }

    if (num < 0.0f) {
        write('-');
        num = -num;
    }

    // Limit the scale to uint32_t and avoid excessive output on an ATtiny.
    if (decimals > 9) decimals = 9;

    if (num >= 4294967296.0f) {
        print("ovf");
        return;
    }

    uint32_t int_part = (uint32_t)num;
    if (decimals == 0) {
        print((uint32_t)(num + 0.5f));
        return;
    }

    float frac = num - (float)int_part;
    uint32_t scale = 1;
    for (uint8_t i = 0; i < decimals; i++) {
        scale *= 10;
    }

    uint32_t fraction = (uint32_t)(frac * scale + 0.5f);
    if (fraction >= scale) {
        int_part++;
        fraction = 0;
    }

    print(int_part);
    write('.');

    uint32_t divisor = scale / 10;
    while (divisor > 0) {
        write((uint8_t)(fraction / divisor) + '0');
        fraction %= divisor;
        divisor /= 10;
    }
}

// Newline
void ATTinySerial::println() {
    write('\r');
    write('\n');
}
