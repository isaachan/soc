void delayUs2x(unsigned char t) {   
  while(--t);
}

void delayMs(unsigned char t) {     
  while(--t) {
    delayUs2x(245);
	  delayUs2x(245);
  }
}
