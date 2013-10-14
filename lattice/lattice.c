#include<reg52.h>
#include<intrins.h>

sbit LATCH = P1^0;
sbit SRCLK = P1^1;
sbit SER   = P1^2;

sbit LATCH_B = P2^2;
sbit SRCLK_B = P2^1;
sbit SER_B   = P2^0;

void sendByte(unsigned char dat) {
  unsigned char i;

  for (i = 0; i < 8; i++) {
    SRCLK = 0;
    SER = dat & 0x80;
    dat <<= 1;
    SRCLK = 1;
  }
}

void send2Byte(unsigned char dat1, unsigned char dat2) {
  sendByte(dat1);
  sendByte(dat2);
}

void out595(void) {
  LATCH = 0;
  _nop_();
  LATCH = 1;
}

void sendSeg(unsigned char dat) {
  unsigned char i;
  for (i = 0; i < 8; i++) {
    SRCLK_B = 0;
    SER_B = dat & 0x80;
    dat <<= 1;
    SRCLK_B = 1;
  }
  LATCH_B = 0;
  _nop_();
  LATCH_B = 1;
}


