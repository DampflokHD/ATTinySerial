#include <ATTinySerial.h>
#include <avr/wdt.h>

ATTinySerial debugSerial;

void setup() {
    uint8_t resetCause = MCUSR;
    MCUSR = 0;
    wdt_disable();

    debugSerial.begin(9600);

    if (resetCause & _BV(WDRF)) {
        debugSerial.println(F("ERROR: watchdog reset"));
    } else {
        debugSerial.println(F("OK: startup"));
    }

    wdt_enable(WDTO_8S);
}

void loop() {
    wdt_reset();
    debugSerial.println(F("ATTinySerial test"));
    debugSerial.write('>');
    debugSerial.println();

    debugSerial.print(F("char: "));
    debugSerial.println('A');
    debugSerial.print(F("string: "));
    debugSerial.println("RAM string");
    debugSerial.print(F("flash: "));
    debugSerial.println(F("Flash string"));

    debugSerial.print(F("bool: "));
    debugSerial.print(true);
    debugSerial.print(' ');
    debugSerial.println(false);

    debugSerial.println((int8_t)-128);
    debugSerial.println((uint8_t)255);
    debugSerial.println((int16_t)-32768);
    debugSerial.println((uint16_t)65535);
    debugSerial.println((int32_t)(-2147483647L - 1L));
    debugSerial.println((uint32_t)4294967295UL);

    debugSerial.print(F("float: "));
    debugSerial.println(23.4567f, 4);
    debugSerial.println(-0.0049f, 3);
    debugSerial.println(12.5f, 0);
    debugSerial.println(1.0f / 3.0f, 9);
    debugSerial.println(NAN, 2);
    debugSerial.println(INFINITY, 2);
    debugSerial.println(-INFINITY, 2);
    debugSerial.println(4294967296.0f, 2);

    wdt_reset();
    debugSerial.println(F("OK: test complete"));
    debugSerial.println();

    delay(5000);
}