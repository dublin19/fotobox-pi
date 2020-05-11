import RPi.GPIO as GPIO
from time import sleep

GPIO.setmode(GPIO.BOARD)
GPIO.setup(37, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)

while True:
    if (GPIO.input(37) == True):
        print('Ausgabe')
        execfile('camera-ftp.py')
        break
    else:
        print('Kein Eingang')
    #sleep(1)
