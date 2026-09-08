#include <ATTinySerial.h>

ATTinySerial mySerial(0);

void setup() {
    mySerial.begin(9600);
}

void loop() {
    float temperature = 24.5678f;
    int32_t uptime = 100000;
    
    mySerial.print(F("Temp: "));
    mySerial.print(temperature, 2); // Prints "24.57"
    mySerial.println(F(" C"));
    
    mySerial.print(F("Uptime: "));
    mySerial.println(uptime);
    
    delay(2000);
}
