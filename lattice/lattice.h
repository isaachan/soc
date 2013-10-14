#ifndef __LATTICE_H__
#define __LATTICE_H__

void sendByte(unsigned char dat);
void send2Byte(unsigned char dat1, unsigned char dat2);
void out595(void);
void sendSeg(unsigned char dat);

#endif