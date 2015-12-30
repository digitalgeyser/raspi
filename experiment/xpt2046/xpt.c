#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <sys/time.h>
#include <string.h>
#include <stdint.h>
#include <linux/spi/spidev.h>
#include <fcntl.h>
#include <sys/ioctl.h>

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


// pass SPI_MODE_0, SPI_MODE_1, SPI_MODE_2 or SPI_MODE_3
void spimode(int channel, int spiMode) {
   int fd;
   char mode;
   
   /* read mode */
   ioctl(fd,SPI_IOC_RD_MODE,&mode);
   printf("SPI mode:  %u -> ",mode);
   if ( channel == 0 )
     fd = open("/dev/spidev0.0", O_RDWR);
   else
     fd = open("/dev/spidev0.1", O_RDWR);
   
   if (fd >= 0) {
      /* write mode */
      mode = spiMode;
      ioctl(fd,SPI_IOC_WR_MODE,&mode);

      /* read mode */
      ioctl(fd,SPI_IOC_RD_MODE,&mode);
      printf("%u\n",mode);
   }

   close(fd);
}

int main (int argc, char **argv) {
  int channel, n, i;
  int spiMode, allzeroes;
  uint8_t data[LEN];
  struct timeval startTime;
  struct timeval tv;

  if ( argc != 3 ) {
    printf("Usage: xpt <channel> <spiMode>\n");
    return;
  }
  
  channel = atoi(argv[1]);
  switch(atoi(argv[2])) {
    case 0: spiMode = SPI_MODE_0; break;
    case 1: spiMode = SPI_MODE_1; break;
    case 2: spiMode = SPI_MODE_2; break;
    case 3: spiMode = SPI_MODE_3; break;
  }
  
  printf("Channel %d, spi mode %d\n", channel, spiMode);
  spimode(channel, spiMode);
  wiringPiSPISetup(channel, FREQUENCY);
  gettimeofday(&startTime, NULL);

  memset(data, 0, LEN);
  
  do {
    data[0] = 0xF7;
    gettimeofday(&tv, NULL);

    printtdiff(&startTime, &tv);
    printf(" - %d:", n);
    for ( i = 0; i<LEN; i++ ) {
      printf("%02x", data[i]);
    }
    n = wiringPiSPIDataRW(channel, data, LEN);
    printf(" => ");
    allzeroes = 1;
    for ( i=0; i<LEN; i++ ) {
      printf("%02x", data[i]);
      if ( data[i] != 0 )
        allzeroes = 0;
    }
    if ( allzeroes ) 
      printf("\r");
    else 
      printf("\n");
    usleep(10000);
  } while(tv.tv_sec - startTime.tv_sec < 10);

  return 0;
}
