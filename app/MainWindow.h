// Fotobox-Software
// Copyright (c) 2020 Jan Kowalewicz <jan.kowalewicz@canon.de>.

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QHBoxLayout>

#include "ImagePreview.h"
#include <QSvgWidget>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool setImage(const QString &pathToImage);
    bool generateQRCode(const QString &fromText);

    void showImage();
    void showQRCode();

#if 0
public slots:
    void onImgLabelClick();
#endif

protected:
    QString imagePath;
    QString qrLink;
    ImagePreview *imgPreview;
    QSvgWidget *qrWidget;

    QWidget *centralWidget;
    QHBoxLayout *mainLayout;
};

#endif // MAIN_WINDOW_H
