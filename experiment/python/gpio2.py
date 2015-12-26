#!/usr/bin/python

import RPi.GPIO as GPIO
import time
import c

delay=0.01

c.init()
c.yellowOff()
c.blueOff()

time.sleep(delay)

button=1
consecutive = 0
while consecutive < 400:
  button = GPIO.input(24)
  if button == 0:
    consecutive += 1
    c.blueOn()
  else:
    consecutive = 0
    c.blueOff()

  if (consecutive/10) % 2 == 0:
    c.yellowOn()
  else:
    c.yellowOff()
   
  time.sleep(delay)


c.cleanup()



