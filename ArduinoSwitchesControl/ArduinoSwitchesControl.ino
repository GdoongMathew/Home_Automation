/*
 * Arduino Micro Extension Cable Switches Controller by Mathew Tung
 * Receiving Data from ESP8266 and change the ON/OFF status of each switches.
 */

#include <SoftwareSerial.h>

SoftwareSerial mySerial (10, 11); //(RX, TX)

int switches[5] = {3, 4, 5, 6, 7};
String inputString = "";         // a String to hold incoming data
boolean stringComplete = false;  // whether the string is complete
void setup() {

  //initialize serial
  Serial.begin(9600);
  mySerial.begin(115200);
  mySerial.println("SoftwareSerial begin");
  for (int i = 0; i<4; i++){
    pinMode(switches[i], OUTPUT);
  }
}

void loop() {

  String inChar;
  while (mySerial.available()) {
    // get the new byte:
    char c = mySerial.read();
    inChar += c;
  }

  inChar.trim();
  if (inChar.length()>0){
    Serial.println(inChar);

    // ASCII to int, and map to the led pins.
    int pinNum = (int)inChar[1] - 97;
    Serial.print("pinNum:");
    Serial.println(pinNum);

    Serial.println(inChar[0]);

    // turn on/off the led.
    if (inChar[0] == '1'){
      Serial.println("Turn on");
      digitalWrite(switches[pinNum], HIGH);
    } else if (inChar[0] == '0'){
      digitalWrite(switches[pinNum], LOW);
      Serial.println("Turn off");
    }
  }
  
}
