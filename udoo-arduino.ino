#include <SPI.h>

void setup() {
  // put your setup code here, to run once:
  SPI.begin();
  Serial.begin(115200);
  Serial1.begin(115200);
  pinMode(A0, INPUT);
}

int i = 0;
int lastMillis = 0;
int adcSums = 0;
int adcSum = 0;
int adcAverage=0;
void loop() {
  //delay(10);
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

}
