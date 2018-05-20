#include <SPI.h>
#include "pins.h"
#include "range.h"
#include "uartTask.h"
#include "encoders.h"


uint16_t fanRpm[3] = {0, 0, 0};

//int lastXpos1=0, lastXpos2=0;

int lastAndrCpuTemp = 0, andrCpuTemp=0;
boolean bFanOn = false;
boolean bHeatOn = false;

int lastSharpVal=0;
int dallasTemp = -99, lastDallasTemp = 0;

char str[50],lastStr[50];
uint64_t lastPhoneMsgRecvTime = 0;

void setup() {
  // put your setup code here, to run once:
  SPI.begin();
  SPI.setDataMode(SPI_MODE3);
  SPI.setClockDivider(SPI_CLOCK_DIV16);
  //SPI.setBitOrder(LSBFIRST);
  Serial.begin(115200);
  Serial1.begin(115200);
  pinMode(PIN_SHARP, INPUT);

  
  pinMode(8, OUTPUT);      
  
  
}

int i = 0;
int lastMillis = 0;
//int adcSums = 0;
//int adcSum = 0;
//int adcAverage=0;
int lastSensItIn = 0;
bool but1 = false;
bool but2 = false;
void loop() {

  but1 = checkSensors(PIN_CAP_SENSOR_0);
  but2 = checkSensors(PIN_CAP_SENSOR_1);
  
  digitalWrite(8, HIGH);   
  //delay(1);
  digitalWrite(8, LOW);   

  checkUart();
  checkRange();
  checkEncoders();
  
//  adcSum += analogRead(A0);
//  adcSums++;
//  if(adcSums>1000){    
//    adcAverage = adcSum/1000;    
//    adcSum = 0;
//    adcSums = 0;
//  }
  
    
  //if(((curTime - lastSendReportTime) > 10) && bDataUpdated){     
    sprintf(&(str[0]), "%04X %04X %04d %01d %01d", xPos1, xPos2, sharpVal, but1, but2);        
    //str[19] = ' '; 
    //sprintf(&(str[20]), "%04d    000 000 000", /*andrCpuTemp*/ 0);

    //str[24] = str[27] = str[31] = str[35] = ' ';      
    //str[39] = 0;

  
    //lastSendReportTime = curTime;
    //bDataUpdated = false;
    if(strcmp(str, lastStr) != 0){
      strcpy(lastStr, str);
      Serial.println(str);        
    }
  //}

  if((millis()-lastMillis)>1000){
    lastMillis = millis();
//    Serial.print("Iters..");
//    Serial.print(i, DEC);
//    Serial.println("");    
//    
//    Serial1.print("Iters..");    
//    Serial1.print(i, DEC);
//    Serial1.println("");    
    i = 0;
  }
  else{
    i++;
  }


}

bool bSoundEnable = false;
bool isSoundEnabled()
{
  return bSoundEnable;  
}

void soundOn()
{
  digitalWrite(PIN_MUTE, LOW);              
  bSoundEnable = true;
}

void soundOff()
{
  digitalWrite(PIN_MUTE, HIGH);  
  bSoundEnable = false;
}

void checkUart()
{
  if(readSerial() == true){
    if(inString == "reset\n"){
      //resetPhone();          
      lastPhoneMsgRecvTime = millis();
    }
    else if(inString == "son\n"){
      soundOn();      
      lastPhoneMsgRecvTime = millis();
    }
    else if(inString == "soff\n"){
      soundOff();      
      lastPhoneMsgRecvTime = millis();
    }
    else if(inString.startsWith("t=") == true){
      inString.remove(0, 2);

      andrCpuTemp = inString.toInt();
      //sprintf(&(str[20]),"%04d", andrCpuTemp);            
      lastPhoneMsgRecvTime = millis();
    }

    else if(inString.startsWith("d=") == true){
      inString.remove(0, 2);

      dallasTemp = inString.toInt();
      //sprintf(&(str[20]),"%04d", andrCpuTemp);            
      lastPhoneMsgRecvTime = millis();
    }
    
    
    inString = "";
  }
}

void formatData()
{
  sprintf(&(str[10]), "%04d %04d %04d    %03x %03x %03x", 
                      dallasTemp, sharpVal, andrCpuTemp, 
                      fanRpm[0], fanRpm[1], fanRpm[2]);
                          
  str[25] = bFanOn? 'E':'D';
  str[26] = bHeatOn? 'E':'D';
}

bool checkSensors(int pinNum)
{
  int iters = 0;
  pinMode(pinNum, OUTPUT);
  //digitalWrite(pinNum, LOW);     
  pinMode(pinNum, INPUT);
  
  for(iters=0; iters<15; iters++){
    if(digitalRead(pinNum) == 1){
      if(iters > 1){            
        //Serial.print(pinNum, DEC);
        //Serial.print(":cap in ");      
        //Serial.print(iters, DEC);
        //Serial.println(""); 
        lastSensItIn = iters;        
      }
      
      break;
    }       
  }
  return iters>1;
}


