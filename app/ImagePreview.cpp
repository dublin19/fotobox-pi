// Fotobox-Software
// Copyright (c) 2020 Jan Kowalewicz <jan.kowalewicz@canon.de>.

#include "ImagePreview.h"
#include <QScrollBar>
#include <QHBoxLayout>
#include <QImageReader>

ImagePreview::ImagePreview(QWidget *parent) : QWidget(parent)
{
    imgLabel = new ClickableLabel;
    imgLabel->setScaledContents(true);

    scrollArea = new QScrollArea;
    scrollArea->setContentsMargins(0,0,0,0);
    scrollArea->setAlignment(Qt::AlignCenter);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->verticalScrollBar()->blockSignals(true);
    scrollArea->horizontalScrollBar()->blockSignals(true);
    scrollArea->setFrameStyle(0);
    scrollArea->setWidget(imgLabel);
    scrollArea->setWidgetResizable(true);

    QHBoxLayout *layout = new QHBoxLayout();
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);
    layout->addWidget(scrollArea);
    setLayout(layout);
}

QPixmap& ImagePreview::loadImage(QString fromFilePath)
{
    QImageReader rd(fromFilePath);
    if (rd.size().isValid())
    {
        QSize resize = rd.size();
        resize.scale(QSize(imgLabel->width(), imgLabel->height()), Qt::KeepAspectRatio);
        QImage previewImage;
        rd.read(&previewImage);
        prevPixmap = QPixmap::fromImage(previewImage);
    }
    imgLabel->setPixmap(prevPixmap);
    resizeImagePreview();
    return prevPixmap;
}

void ImagePreview::clear()
{
    imgLabel->clear();
}

void ImagePreview::resizeImagePreview()
{
    const QPixmap *pixmap = imgLabel->pixmap();
    if (!pixmap) return;

    QSize prevSizePixmap = pixmap->size();
    if (prevSizePixmap.width() > scrollArea->width() || prevSizePixmap.height() > scrollArea->height())
    {
        prevSizePixmap.scale(scrollArea->width(), scrollArea->height(), Qt::KeepAspectRatio);
    }
    imgLabel->setFixedSize(prevSizePixmap);
    imgLabel->adjustSize();
}
