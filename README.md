# ATTinySerial

**An Ultra-Minimalist, High-Performance UART TX Library for AVR ATtiny Microcontrollers**

The ATtiny microcontroller series (such as the ATtiny13, ATtiny25, ATtiny45, and ATtiny85) offers immense flexibility in a highly compact form factor. However, these devices suffer from severe Flash memory constraints (as low as 1KB) and a limited number of hardware timers. 

Standard communication libraries like `SoftwareSerial` are often too bloated for these controllers, consuming valuable timers and significant portions of Flash and RAM. **ATTinySerial** was developed to solve this problem by providing a highly optimized, TX-only (Transmit) bit-banging implementation that requires zero hardware timers and reduces function-call overhead to an absolute minimum.

---

## Core Features

* **Zero Hardware Timer Dependency:** 
  The library performs precise software-based timing using the highly predictable `_delay_loop_2` intrinsic function. This frees up the internal hardware timers (Timer0/Timer1) entirely for user applications like PWM generation, millis() tracking, or hardware interrupts.
* **Aggressive Flash Optimization via Inline Wrappers:** 
  To prevent the compiler from generating costly jump instructions and stack operations for formatting variants (e.g., appending newlines or casting integer types), `ATTinySerial` implements these wrappers as `inline` methods directly within the header file. This leads to near-zero abstraction overhead in the compiled binary.
* **Interrupt-Safe Bit-Banging:** 
  UART timing is highly sensitive to external interrupts. The library temporarily saves the Status Register (`SREG`), clears the global interrupt flag during the transmission of a single byte, and restores the state immediately after the stop bit.
* **Robust Numeric and Floating-Point Handling:** 
  Unlike many minimalist libraries that strip out floating-point math, `ATTinySerial` includes a robust implementation. It correctly handles `NaN` and `Infinity` states, provides 32-bit integer overflow protection, and natively implements rounding (e.g., rounding `0.999` correctly based on the specified decimal precision) without relying on bloated standard library implementations like `sprintf`.
* **Instruction Cycle Compensation:**
  The internal delay calculation automatically subtracts the required clock cycles needed for bit-shifting and loop operations (`cycles -= 3`), ensuring accurate baud rates even at low CPU frequencies.

---

## Architecture and Technical Design

### Hardware Port Optimization
Inside the core `write(char c)` function, pointer referencing is utilized to cache the `PORTB` register. Bitmasks for the specific TX pin and its inverse are pre-calculated before the critical timing section begins. This ensures that the state changes inside the bit-banging `for`-loop are executed in the minimum possible number of clock cycles (typically using `LD` and `ST` or `OUT` assembly instructions).

### Memory Management with PROGMEM
RAM is the most scarce resource on an ATtiny (the ATtiny13 possesses only 64 Bytes). To prevent string literals from being copied to SRAM during initialization, the library natively supports the `__FlashStringHelper` class. Wrapping strings in the `F()` macro forces the compiler to keep the data in Flash memory, reading it byte-by-byte via `pgm_read_byte()`.

---

## Installation

### Arduino IDE
1. Download this repository as a `.zip` file.
2. Open the Arduino IDE.
3. Navigate to **Sketch** > **Include Library** > **Add .ZIP Library...**
4. Select the downloaded `.zip` archive.

### PlatformIO
If you are using PlatformIO, you can clone the repository directly into your `lib/` directory or include it via `platformio.ini`:
```ini
lib_deps =
    ATTinySerial=[https://github.com/YOUR_GITHUB_USERNAME/ATTinySerial.git](https://github.com/YOUR_GITHUB_USERNAME/ATTinySerial.git)
