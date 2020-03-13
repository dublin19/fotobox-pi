import ftplib, glob, os
session = ftplib.FTP('dublin19.bplaced.net', 'dublin19_fotoboxuser', 'fotobox')

os.chdir("/home/fotobox-user/fotobox-app/new_image")
for file in glob.glob("*.jpg"):
    ftpfile = open(file, 'rb')
    session.storbinary('STOR ' + file, ftpfile)
    with open("/home/fotobox-user/fotobox-app/new_image/info.txt", 'w') as infofile:
        infofile.write('http://dublin19.bplaced.net/fotoboximages/' + file)
    ftpfile.close()
    session.quit()
