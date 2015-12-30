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
void spimode(int channel, int mode) 
{
   int fd;
   char mode;

   if ( channel == 0 )
     fd = open("/dev/spidev0.0", O_RDWR);
     else
   fd = open("/dev/spidev0.1", O_RDWR);

   if (fd >= 0)
   {
      /* write mode */
      mode = mode;
      ioctl(fd,SPI_IOC_WR_MODE,&mode);

      /* read mode */
      ioctl(fd,SPI_IOC_RD_MODE,&mode);
      printf("mode = %u\n",mode);
   }

   close(fd);
}

int main (int argc, char **argv)
{
  int channel, n, i;
  uint8_t data[LEN];
  struct timeval startTime;
  struct timeval tv;
  
  channel = 0;
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
