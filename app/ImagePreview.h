// Fotobox-Software
// Copyright (c) 2020 Jan Kowalewicz <jan.kowalewicz@canon.de>.

#ifndef IMAGE_PREVIEW_H
#define IMAGE_PREVIEW_H

#include <QWidget>
#include <QObject>
#include "ClickableLabel.h"
#include <QScrollArea>
#include <QPixmap>

class ImagePreview : public QWidget
{
    Q_OBJECT
public:
    ImagePreview(QWidget *parent = nullptr);

    QPixmap &loadImage(QString fromFilePath);

    void resizeImagePreview();

    void clear();

    QScrollArea *scrollArea;

    ClickableLabel *imgLabel;

protected:
    QPixmap prevPixmap;
};

#endif // IMAGE_PREVIEW_H
