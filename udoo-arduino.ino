#include <SPI.h>
#include "pins.h"
#include "range.h"




uint16_t fanRpm[3] = {0, 0, 0};

int lastXpos1=0, lastXpos2=0;
int xPos1 = 0, xPos2 = 0;

int lastAndrCpuTemp = 0, andrCpuTemp=0;
boolean bFanOn = false;
boolean bHeatOn = false;

int lastSharpVal=0;
int dallasTemp = -99, lastDallasTemp = 0;

char str[50];//, lastStr[50];
void setup() {
  // put your setup code here, to run once:
  SPI.begin();
  Serial.begin(115200);
  Serial1.begin(115200);
  pinMode(PIN_SHARP, INPUT);

  
  pinMode(8, OUTPUT);  
  
}

int i = 0;
int lastMillis = 0;
int adcSums = 0;
int adcSum = 0;
int adcAverage=0;
void loop() {
  digitalWrite(8, HIGH);   
  //delay(1);
  digitalWrite(8, LOW);   
  
  SPI.transfer(0xab);
  SPI.transfer(0xed);
  i++;
  
  adcSum += analogRead(A0);
  adcSums++;
  if(adcSums>1000){    
    adcAverage = adcSum/1000;    
    adcSum = 0;
    adcSums = 0;
  }
  
  if((millis()-lastMillis)>1000){
    lastMillis = millis();
    Serial.print("Iters..");
    Serial.print(adcAverage, DEC);    
    Serial.print("..");
    Serial.print(i, DEC);
    Serial.println("");    
    
    Serial1.print("Iters..");
    Serial1.print(adcAverage, DEC);    
    Serial1.print("..");
    Serial1.print(i, DEC);
    Serial1.println("");    

  }


  checkRange();
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

void formatData()
{
  sprintf(&(str[10]), "%04d %04d %04d    %03x %03x %03x", 
                      dallasTemp, sharpVal, andrCpuTemp, 
                      fanRpm[0], fanRpm[1], fanRpm[2]);
                          
  str[25] = bFanOn? 'E':'D';
  str[26] = bHeatOn? 'E':'D';
}



