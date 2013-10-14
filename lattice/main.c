#include <reg52.h>    
#include <intrins.h> 
#include "delay.h"
#include "lattice.h"

unsigned char segout[8]    = { 0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80 }; 
unsigned char code heart[] = { 0x00,0x6C,0x92,0x82,0x44,0x28,0x10,0x00 };

void main()
{
  unsigned char i;
  while(1)
  {  
    for(i = 0; i < 8; i++) //8апотй╬
    {
      sendSeg(segout[i]);
      
      send2Byte(~heart[i], 0xFF);
      out595();
      delayMs(1);
      
      send2Byte(0xFF,0xFF);
      out595();
    }          
  }
}


