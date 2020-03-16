import RPi.GPIO as GPIO
from time import sleep

GPIO.setmode(GPIO.BOARD)
GPIO.setup(37, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)

while True:
    if (GPIO.input(37) == True):
        # TODO: break und Bild aufnehmen
        print('Ausgabe')
    else:
        print('Kein Eingang')
    sleep(1)
