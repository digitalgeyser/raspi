#include <wiringPi.h>
#include <unistd.h>

#define BLUE 18
#define YELLOW 17
#define BUTTON 24

#define yellowOn() digitalWrite(YELLOW, HIGH)
#define yellowOff() digitalWrite(YELLOW, LOW)
#define blueOn() digitalWrite(BLUE, HIGH)
#define blueOff() digitalWrite(BLUE, LOW)

void init() {
  wiringPiSetupGpio() ;
  pinMode (BLUE, OUTPUT) ;
  pinMode (YELLOW, OUTPUT) ;
  pinMode (BUTTON, INPUT ) ;
  pullUpDnControl(BUTTON, PUD_UP);
}

void cleanup() {
  yellowOff();
  blueOff();
}



int main (void)
{
  int diff=1;
  int button=1;
  int consecutive=0;

  init();
  while(consecutive<400) {
    button = digitalRead(BUTTON);
    if ( button == LOW ) {
      consecutive += diff;
      blueOn();
    } else {
      consecutive = 0;
      blueOff();
    }
    
    if ( consecutive > 200 )
      diff = 2;

    if ( (consecutive/10) % 2 == 0 ) {
      yellowOn();
    } else {
      yellowOff();
    }
    usleep(10000);
  }
  cleanup();
  return 0 ;
}
