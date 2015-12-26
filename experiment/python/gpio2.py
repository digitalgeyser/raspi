import RPi.GPIO as GPIO
import time

delay=0.01

GPIO.setmode(GPIO.BCM)

print "GPIO mode: ", GPIO.getmode(), "(BCM = ", GPIO.BCM, ", BOARD = ", GPIO.BOARD, ")"
print "GPIO RPI info:", GPIO.RPI_INFO
print "GPIO version: ", GPIO.VERSION
print "\nPush the button for 5 seconds to quit..."

GPIO.setup(18, GPIO.OUT, initial=GPIO.HIGH)
GPIO.setup(17, GPIO.OUT, initial=GPIO.LOW)
GPIO.setup(24, GPIO.IN, pull_up_down=GPIO.PUD_UP)

# Turn off stuff
GPIO.output(18, GPIO.LOW)
GPIO.output(17, GPIO.LOW)

time.sleep(delay)

button=1
consecutive = 0
while consecutive < 400:
  button = GPIO.input(24)
  if button == 0:
    consecutive += 1
    GPIO.output(18, GPIO.HIGH)
  else:
    consecutive = 0
    GPIO.output(18, GPIO.LOW)

  if (consecutive/10) % 2 == 0:
    GPIO.output(17, GPIO.HIGH)
  else:
    GPIO.output(17, GPIO.LOW)
   
  time.sleep(delay)


GPIO.cleanup()



