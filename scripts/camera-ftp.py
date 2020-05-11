from time import sleep
from sh import gphoto2 as gp
from sh import mkdir as mkd
from datetime import datetime
import signal, os, subprocess, shutil
import ftplib, glob, os
session = ftplib.FTP('dublin19.bplaced.net', 'dublin19_fotoboxuser', 'fotobox')

def startSoftware():
    subprocess.call('/home/fotobox-user/_fotobox-pi-SOURCE/fotobox-pi/app/build/debug/fotoboxapp')

def ftpUpload():
    os.chdir("/home/fotobox-user/fotobox-app/new_image")
    for file in glob.glob("*.jpg"):
        ftpfile = open(file, 'rb')
        session.storbinary('STOR ' + file, ftpfile)
        with open("/home/fotobox-user/fotobox-app/new_image/info.txt", 'w') as infofile:
            infofile.write('http://dublin19.bplaced.net/fotoboximages/' + file)
            print("Bild wurde hochgeladen, fallback_link: http://dublin19.bplaced.net/fotoboximages/" + file)
        ftpfile.close()
        session.quit()

def killProc():
    p = subprocess.Popen(['ps', '-A'], stdout=subprocess.PIPE)
    out, err = p.communicate()

    for line in out.splitlines():
        if b'gvfsd-gphoto2' in line:
            pid = int(line.split(None,1)[0])
            os.kill(pid, signal.SIGKILL)

def clearForNewImage():
    shutil.rmtree(save_location)

captureAndGetCommand = ["--capture-image-and-download"]

save_location = "/home/fotobox-user/fotobox-app/new_image"

def captureImage():
    sleep(5)
    os.chdir(save_location)
    gp(captureAndGetCommand)
    for filename in os.listdir(save_location):
        if filename.endswith(".jpg"):
            os.rename(filename, (shot_time + shot_date + ".jpg"))
            print("Aufgenommenes Bild mit Zeitstempel versehen und umbenannt")

if __name__ == "__main__":
    shot_date = datetime.now().strftime("%d-%m-%Y");
    shot_time = datetime.now().strftime("%H:%M:%S");
    clearForNewImage()
    mkd(save_location)
    killProc()    
    captureImage()
    ftpUpload()
    sleep(3)
    startSoftware()
