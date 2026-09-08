#include <ATTinySerial.h>

ATTinySerial serial(0);

void setup() {
    serial.begin(9600);
}

void loop() {
    float temperature = 24.5678f;
    int32_t uptime = 100000;
    
    serial.print(F("Temp: "));
    serial.print(temperature, 2); // Prints "24.57"
    serial.println(F(" C"));
    
    serial.print(F("Uptime: "));
    serial.println(uptime);
    
    delay(2000);
}