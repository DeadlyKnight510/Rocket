#include "log.hpp"
#include "common.hpp"
#include "Arduino.h"
#include "SoftwareSerial.h"

SoftwareSerial bluetooth(BLUETOOTH_RX, BLUETOOTH_TX); // RX, TX

void setup() {
  Serial.begin(PC_BAUD);
  Serial.println("start transmission");
  bluetooth.begin(BLUETOOTH_BAUD);
  bluetooth.println("s - start logging for 60s \ng - get logs \nc - get current height \nz - zero altitude");
}

void loop() { // run over and over
    if (bluetooth.available()) {
        char in = bluetooth.read();
        //get current height
        if(in == 'C' || in == 'c') bluetooth.print(get_height() - zero); bluetooth.print(" meters");
        //zero barometer
        if(in == 'z' || in == 'Z') zero = get_height();
        //start logging
        if(in == 's' || in == 'S') start_log();
        //print the current height
        if(in == 'g' || in == 'G') {
            for(int x = 0; x < 240; x++) {
                bluetooth.print( ((float)x) /LOGS_PER_SEC);
                bluetooth.print("s : ");
                bluetooth.print( (((float)logs[x])/LOG_SCALE) -zero);
                bluetooth.print("m\n");
            }
        }
    }
    update_timer();
}
