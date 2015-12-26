#!/usr/bin/python

import RPi.GPIO as GPIO
import time
import c

delay=0.05
blue=18
yellow=17

c.init()
print "\nPush the button to quit..."
c.blueOn()
c.yellowOff()

time.sleep(delay)

button=1
x = 1
while button > 0:
  x+=1
  c.blueOn()
  c.yellowOff()
  time.sleep(delay)
  c.blueOff()
  c.yellowOn()
  time.sleep(delay)
  button = GPIO.input(24)

c.blueOn()
c.yellowOn()
time.sleep(0.5)

GPIO.cleanup()



