#include <ATTinySerial.h>

// Instantiate the object using default TX pin PB0
ATTinySerial mySerial;

void setup() {
    // Initialize UART at 9600 baud
    mySerial.begin(9600);
}

void loop() {
    mySerial.println("ATtiny is running.");
    delay(1000);
}
