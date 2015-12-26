import RPi.GPIO as GPIO

delay=0.05
blue=18
yellow=17

def init():
  GPIO.setmode(GPIO.BCM)
  print "GPIO mode: ", GPIO.getmode(), "(BCM = ", GPIO.BCM, ", BOARD = ", GPIO.BOARD, ")"
  print "GPIO RPI info:", GPIO.RPI_INFO
  print "GPIO version: ", GPIO.VERSION
  GPIO.setup(18, GPIO.OUT, initial=GPIO.HIGH)
  GPIO.setup(17, GPIO.OUT, initial=GPIO.LOW)
  GPIO.setup(24, GPIO.IN, pull_up_down=GPIO.PUD_UP)

def cleanup():
  GPIO.cleanup()

def blueOn():
  GPIO.output(blue, GPIO.HIGH)

def blueOff():
  GPIO.output(blue, GPIO.LOW)

def yellowOn():
  GPIO.output(yellow, GPIO.HIGH)

def yellowOff():
  GPIO.output(yellow, GPIO.LOW)

