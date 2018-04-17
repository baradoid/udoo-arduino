#include <Arduino.h>
#include "pins.h"
int collectedVals=0;
long  averVal = 0;
int sharpVal = 0;

int calcPoly(int mV, int mV1, int mV2, int cm1, int cm2);
int recalcMvToCm(int mV);

void checkRange()
{
    for(int i=0; i<101; i++){
      averVal += analogRead(PIN_SHARP );
      collectedVals++;
  }
  if(collectedVals>=300){
    averVal /= 300;
    //int mV = fir(averVal)*4.9; //in mV
    int mV = averVal*4.9; //in mV    
    sharpVal = recalcMvToCm(mV);
    
    collectedVals = 0;
    averVal = 0;
  }
  
}

int calcPoly(int mV, int mV1, int mV2, int cm1, int cm2)
{
  float d = abs(mV1-mV2) / (float)abs(cm1-cm2);
  int dist = 60;
  if(d > 0){
    dist = ((mV1-mV)/d) + cm1;
  }
  return dist;
}


int recalcMvToCm(int mV)
{
  int dist = 0;
  if(mV < 500){              
    dist = calcPoly(mV, 500, 250, 25, 40); //500to250 mv = 25to40; 
  }
  else if(mV < 1000){              
    dist = calcPoly(mV, 1000, 500, 12, 25); //1000to500 mv = 12to25;
  }
  else{          
    dist = calcPoly(mV, 3000, 1000, 3,12);   //3000to1000 mv = 3to12
  }
  return dist;
  
}
