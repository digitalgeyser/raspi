#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>

#define CHANNEL 1
#define LEN 1000

int main (void)
{
  int n;
  char data[LEN];
  wiringPiSPISetup(CHANNEL, 500000);
  while(1) {
    n = wiringPiSPIDataRW(CHANNEL, data, LEN); 
    printf("Received: %d\n");
    usleep(1000);
  }
}
