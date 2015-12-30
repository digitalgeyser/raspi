#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <sys/time.h>
#include <string.h>
#include <stdint.h>

//125 kHz is max
#define FREQUENCY 100000
#define LEN 2

static int printtdiff(struct timeval *start, struct timeval *current) {
  if ( current -> tv_usec >= start -> tv_usec ) {
    printf("%05ld.%06ld",
	   current->tv_sec - start -> tv_sec,
	   current->tv_usec - start -> tv_usec);
  } else {
    printf("%05ld.%06ld",
	   current->tv_sec - start ->tv_sec - 1,
	   1000000 + current->tv_usec - start -> tv_usec);
  }
}

int main (int argc, char **argv)
{
  int channel, n, i;
  uint8_t data[LEN];
  struct timeval startTime;
  struct timeval tv;
  
  channel = 1;
  wiringPiSPISetup(channel, FREQUENCY);
  gettimeofday(&startTime, NULL);

  memset(data, 0, LEN);
  
  while(1) {
    data[0] = 0xF7;
    gettimeofday(&tv, NULL);

    printtdiff(&startTime, &tv);
    printf(" - %d:", n);
    for ( i = 0; i<LEN; i++ ) {
      printf("%02x", data[i]);
    }
    n = wiringPiSPIDataRW(channel, data, LEN);
    printf(" => ");
    for ( i=0; i<LEN; i++ ) {
      printf("%02x", data[i]);
    }
    printf("\n");
    usleep(10000);
  }
}
