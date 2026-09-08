/**
 * @file ATTinySerial.h
 * @author DampflokHD
 * @brief Ultra-minimalist UART TX library for ATtiny microcontrollers.
 * @version 1.0.6
 * @date 2026-09-08
 * 
 * @copyright Copyright (c) 2026 DampflokHD. Licensed under the MIT License.
 */

#pragma once

#include <stdint.h>
#include <avr/pgmspace.h>


class __FlashStringHelper;

#ifndef F
#define F(string_literal) (reinterpret_cast<const __FlashStringHelper *>(PSTR(string_literal)))
#endif


class ATTinySerial {
    private:
        uint16_t delay_cycles;
        uint8_t tx_pin;

    public:
        ATTinySerial(uint8_t pin = 0); // Default TX pin PB0

        void begin(uint32_t baudrate);  // Initialize with baud rate (uses default pin or pin set via constructor)
        void begin(uint32_t baudrate, uint8_t pin);  // Initialize with baud rate and specific pin

        // Write a single character
        void write(char c);

        // Strings and single characters
        void print(char c);
        void print(const char* str);  // Print a string
        void print(const __FlashStringHelper* str);  // Print a string from Flash

        // Booleans
        void print(bool b); // Print boolean value (true/false)

        // Integers
        void print(int8_t num);
        void print(uint8_t num);
        void print(int16_t num);
        void print(uint16_t num);
        void print(int32_t num);
        void print(uint32_t num);

        // Floats
        void print(float num, uint8_t decimals = 2);  // Print a float value with specified decimal places
 
    
        // Newline functions
        void println();  // Print a newline

        // Inline wrappers

        // Strings and single characters with newline
        inline void println(char c) { print(c); println(); }
        inline void println(const char* str) { print(str); println(); }
        inline void println(const __FlashStringHelper* str) { print(str); println(); }

        // Booleans with newline
        inline void println(bool b) { print(b); println(); }

        // Integers newline
        inline void println(int8_t num) { print(num); println(); }
        inline void println(uint8_t num) { print(num); println(); }
        inline void println(int16_t num) { print(num); println(); }
        inline void println(uint16_t num) { print(num); println(); }
        inline void println(int32_t num) { print(num); println(); }
        inline void println(uint32_t num) { print(num); println(); }

        // Floats with newline
        inline void println(float num, uint8_t decimals = 2) { print(num, decimals); println(); }
};
