#include <wiringPi.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define GPIO_BACKLIGHT 4

#define backlightOn() digitalWrite(GPIO_BACKLIGHT, HIGH)
#define backlightOff() digitalWrite(GPIO_BACKLIGHT, LOW)

void init() {
  wiringPiSetupGpio() ;
  pinMode (GPIO_BACKLIGHT, OUTPUT) ;
}

void cleanup() {
  backlightOff();
}



int main (int argc, char **argv)
{
  int gpio = atoi(argv[1]);
  int n = 0;

  init();
  backlightOn();
  printf("Using GPIO: %d\n", gpio);
  pinMode (gpio, OUTPUT) ;
  digitalWrite(gpio, LOW);
  while ( n < 10 ) {
    usleep(100000);
    n++;
  }
  digitalWrite(gpio, HIGH);
  cleanup();
  return 0 ;
}
