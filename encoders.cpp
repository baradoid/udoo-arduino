#include <SPI.h>

int xPos1 = 0, xPos2 = 0;

void checkEncoders()
{
  xPos1 = (SPI.transfer16(0xab)>>2)&0x1fff;
  //xPos2 = (SPI.transfer16(0xed)>>4)&0x1fff;
  
}

