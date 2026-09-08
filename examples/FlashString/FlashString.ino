#include <ATTinySerial.h>

ATTinySerial mySerial(2); // Set TX pin to PB2

void setup() {
    mySerial.begin(9600);
    
    // The F() macro prevents the string from consuming scarce RAM
    mySerial.println(F("This string lives in Flash Memory!"));
}

void loop() {
    // Nothing to do here
}
