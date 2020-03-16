import RPi.GPIO as GPIO
from time import sleep

GPIO.setmode(GPIO.BOARD)
GPIO.setup(33, GPIO.OUT)

def turnLightOff():
    GPIO.output(33, GPIO.LOW)
    print 'Licht aus'

def turnLightOn():
    GPIO.output(33, GPIO.HIGH)
    print 'Licht an'

if __name__ == "__main__":
    sleep(1)
    turnLightOn()
    sleep(1)
    turnLightOff()
    sleep(1)
    turnLightOn()
    sleep(1)
    turnLightOff()
    sleep(1)
    turnLightOn()
    execfile('conform.py')
