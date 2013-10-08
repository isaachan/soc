#include<reg52.h>

#define DataPort P0

sbit KEY_HOURS   = P3^3;
sbit KEY_MINS    = P3^4;

sbit LATCH1 = P2^2; // Duan
sbit LATCH2 = P2^3; // Wei

unsigned char hours, mins, seconds;

unsigned char code duanMa[] = {
  0x3f, 0x06, 0x5b, 0x4f,
  0x66, 0x6d, 0x7d, 0x07,
  0x7f, 0x6f
};

unsigned char code weiMa[] = {
  0xfe, 0xfd, 0xfb, 0xf7,
  0xef, 0xdf, 0xbf, 0x7f
};

unsigned char tempData[8];

void delayUs2x(unsigned char t);
void delayMs(unsigned char t);
void display(unsigned char firstBit, unsigned char num);
void initTimer0(void);
void setupDisplayContent();
void inscreaseHour();
void checkHourConfigButton();
void checkMinConfigButton();

void inscreaseHour() {
  hours++;
  if (hours == 24) hours = 0;
}

void inscreaseMin() {
  mins++;
  if (mins == 60) mins = 0;
}

void checkHourConfigButton() {
  unsigned char keyPressNum = 0;
  if (!KEY_HOURS) {
    delayMs(10);
    if (!KEY_HOURS) {
      while(!KEY_HOURS) {
        keyPressNum++;
        delayMs(10);
        if (keyPressNum == 100) {
          keyPressNum = 0;
          while (!KEY_HOURS) {
            inscreaseHour();
            setupDisplayContent();
            delayMs(50);
          }
        }
      }
      inscreaseHour();
    }
  }
}

void checkMinConfigButton() {
  unsigned char keyPressNum = 0;
  if (!KEY_MINS) {
    delayMs(10);
    if (!KEY_MINS) {
      while(!KEY_MINS) {
        keyPressNum++;
        delayMs(10);
        if (keyPressNum == 100) {
          keyPressNum = 0;
          while (!KEY_MINS) {
            inscreaseMin();
            setupDisplayContent();
            delayMs(50);
          }
        }
      }
      inscreaseMin();
    }
  }
}

void main(void) {

  KEY_HOURS = 1;
  initTimer0();

  while(1) {
    checkHourConfigButton();
    checkMinConfigButton();
    setupDisplayContent();
  }
}

void setupDisplayContent() {
  tempData[0] = duanMa[hours/10];
  tempData[1] = duanMa[hours%10];
  tempData[2] = 0x40;
  tempData[3] = duanMa[mins/10];
  tempData[4] = duanMa[mins%10];
  tempData[5] = 0x40;
  tempData[6] = duanMa[seconds/10];
  tempData[7] = duanMa[seconds%10];
}

void delayUs2x(unsigned char t) {
  while (--t);
}

void delayMs(unsigned char t) {
  while (--t) {
    delayUs2x(245);
    delayUs2x(245);
  }
}

void display(unsigned char firstBit, unsigned char num) {
  static unsigned char i;
  DataPort = 0;
  LATCH1 = 1;
  LATCH1 = 0;

  DataPort = weiMa[i + firstBit];
  LATCH2 = 1;
  LATCH2 = 0;

  DataPort = tempData[i];
  LATCH1 = 1;
  LATCH1 = 0;  

  i++;
  if (i == num) i = 0;
}

void initTimer0(void) {
  TMOD |= 0x01;
  EA = 1;
  ET0 = 1;
  TR0 = 1;
}

void timerIsr(void) interrupt 1 {
  static unsigned int t;
  TH0 = (65536 - 2000) / 256;  //2ms
  TL0 = (65536 - 2000) % 256;
  display(0, 8);
  
  t++;
  if (t == 500) {
    t = 0;
    seconds++;
    if (seconds == 60) {
      seconds = 0;
      mins++;
      if (mins == 60) {
        mins = 0;
        hours++;
        if (hours == 24) {
          hours = 0;
        }
      }
    }
  }

}












































