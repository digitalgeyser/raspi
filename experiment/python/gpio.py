import RPi.GPIO as GPIO
import time

delay=0.05

GPIO.setmode(GPIO.BCM)

print "GPIO mode: ", GPIO.getmode(), "(BCM = ", GPIO.BCM, ", BOARD = ", GPIO.BOARD, ")"
print "GPIO RPI info:", GPIO.RPI_INFO
print "GPIO version: ", GPIO.VERSION
print "\nPush the button to quit..."

GPIO.setup(18, GPIO.OUT, initial=GPIO.HIGH)
GPIO.setup(17, GPIO.OUT, initial=GPIO.LOW)
GPIO.setup(24, GPIO.IN, pull_up_down=GPIO.PUD_UP)

GPIO.output(18, GPIO.HIGH)
GPIO.output(17, GPIO.HIGH)

time.sleep(delay)

button=1
x = 1
while button > 0:
  x+=1
  GPIO.output(18, GPIO.HIGH)
  GPIO.output(17, GPIO.LOW)
  time.sleep(delay)
  GPIO.output(18, GPIO.LOW)
  GPIO.output(17, GPIO.HIGH)
  time.sleep(delay)
  button = GPIO.input(24)


GPIO.output(18, GPIO.HIGH)
GPIO.output(17, GPIO.HIGH)
time.sleep(0.5)

GPIO.cleanup()



