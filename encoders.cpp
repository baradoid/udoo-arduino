#include <SPI.h>

int xPos1 = 0, xPos2 = 0;

void checkEncoders()
{
  SPI.transfer(0xab);
  SPI.transfer(0xed);
  
}

