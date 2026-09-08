#include <ATTinySerial.h>

// Instantiate the object using default TX pin PB0
ATTinySerial serial;

void setup() {
    // Initialize UART at 9600 baud
    serial.begin(9600);
}

void loop() {
    serial.println("ATtiny is running.");
    delay(1000);
}
