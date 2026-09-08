#include <ATTinySerial.h>
#include <avr/wdt.h>

ATTinySerial mySerial;

void setup() {
    uint8_t resetCause = MCUSR;
    MCUSR = 0;
    wdt_disable();

    mySerial.begin(9600);

    if (resetCause & _BV(WDRF)) {
        mySerial.println(F("ERROR: watchdog reset"));
    } else {
        mySerial.println(F("OK: startup"));
    }

    wdt_enable(WDTO_8S);
}

void loop() {
    wdt_reset();
    mySerial.println(F("ATTinySerial test"));
    mySerial.write('>');
    mySerial.println();

    mySerial.print(F("char: "));
    mySerial.println('A');
    mySerial.print(F("string: "));
    mySerial.println("RAM string");
    mySerial.print(F("flash: "));
    mySerial.println(F("Flash string"));

    mySerial.print(F("bool: "));
    mySerial.print(true);
    mySerial.print(' ');
    mySerial.println(false);

    mySerial.println((int8_t)-128);
    mySerial.println((uint8_t)255);
    mySerial.println((int16_t)-32768);
    mySerial.println((uint16_t)65535);
    mySerial.println((int32_t)(-2147483647L - 1L));
    mySerial.println((uint32_t)4294967295UL);

    mySerial.print(F("float: "));
    mySerial.println(23.4567f, 4);
    mySerial.println(-0.0049f, 3);
    mySerial.println(12.5f, 0);
    mySerial.println(1.0f / 3.0f, 9);
    mySerial.println(NAN, 2);
    mySerial.println(INFINITY, 2);
    mySerial.println(-INFINITY, 2);
    mySerial.println(4294967296.0f, 2);

    wdt_reset();
    mySerial.println(F("OK: test complete"));
    mySerial.println();

    delay(5000);
}
