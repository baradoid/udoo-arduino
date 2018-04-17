#include <Arduino.h>
String inString = ""; 

bool readSerial()
{  
  bool ret = false;
  while (Serial.available() > 0) {
    int inChar = Serial.read();
    //if (isDigit(inChar)) {
      // convert the incoming byte to a char
      // and add it to the string:
      inString += (char)inChar;
    //}

    if (inChar == '\n') {
      //andrCpuTemp = inString.toInt();
      //inString = "";
      ret = true;
      break;              
    }
  }
  return ret;
}

