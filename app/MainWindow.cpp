// Fotobox-Software
// Copyright (c) 2020 Jan Kowalewicz <jan.kowalewicz@canon.de>.

#include "MainWindow.h"
#include "third/QrCode.hpp"
#include <QByteArray>
#include <QString>
#include <QStandardPaths>
#include <QFileInfo>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QDir>

using namespace qrcodegen;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setStyleSheet("background-color: black;");
    resize(QSize(1440, 900));
    // Wir überprüfen ob in unserem Ordner "new_image" die Datei "info.txt" liegt.
    const QString folderPath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/fotobox-app/new_image";
    QFileInfo infoExists(folderPath + "/info.txt");
    if (infoExists.exists())
    {
        // Wir müssen definitiv ein Bild in dem Ordner haben.
        QStringList filter("*.jpg");
        QDir directory(folderPath);
        QStringList files = directory.entryList(filter);
        QString file = files.at(0); // das erste Ergebnis aus dem Array

        imagePath = folderPath + "/" + file;

        // Jetzt lesen wir den FTP Link aus der Info-Datei aus.
        QFile f(folderPath + "/info.txt");
        if (f.open(QIODevice::ReadOnly))
        {
            QTextStream rd(&f);
            qrLink = rd.readAll();
            f.close();
        }
    }
    else
    {
        // kein Bild...?
    }

    centralWidget = new QWidget(this);
    mainLayout = new QHBoxLayout(this);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    if (!imagePath.isEmpty())
    {
        if (!qrLink.isEmpty())
        {
            showImage();
            showQRCode();
        }
    }

    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

#if 0
    if (!imagePath.isEmpty())
    {
        showImage();
        connect(imgPreview->imgLabel, SIGNAL(clicked()), SLOT(onImgLabelClick()));
    }
#endif

}

MainWindow::~MainWindow()
{
    imagePath = "";
    qrLink = "";
}

bool MainWindow::setImage(const QString &pathToImage)
{
    imgPreview->loadImage(pathToImage);
}

bool MainWindow::generateQRCode(const QString &withText)
{
    QrCode qr = QrCode::encodeText(withText.toStdString().c_str(), QrCode::Ecc::MEDIUM);
    std::string stdSVGString = qr.toSvgString(4);

    QByteArray svgByteArray(stdSVGString.c_str(), stdSVGString.length());
    qrWidget->load(svgByteArray);
}

void MainWindow::showImage()
{
    imgPreview = new ImagePreview(this);
    //mgPreview->scrollArea->setFixedSize(QSize(640, 480));
    //imgPreview->setMaximumWidth(720);
    setImage(imagePath);
    //setCentralWidget(imgPreview);
    mainLayout->addWidget(imgPreview);
}

void MainWindow::showQRCode()
{
    qrWidget = new QSvgWidget(this);
    qrWidget->setMaximumSize(QSize(480, 480));
    qrWidget->setMinimumWidth(480);
    generateQRCode(qrLink);
    //setCentralWidget(qrWidget);
    mainLayout->addWidget(qrWidget);
}

#if 0
void MainWindow::onImgLabelClick()
{
    showQRCode();
}
#endif
