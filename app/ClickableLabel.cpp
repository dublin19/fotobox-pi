// Fotobox-Software
// Copyright (c) 2020 Jan Kowalewicz <jan.kowalewicz@canon.de>.

#include "ClickableLabel.h"

ClickableLabel::ClickableLabel(QWidget *parent) : QLabel(parent)
{
}

ClickableLabel::~ClickableLabel()
{
}

void ClickableLabel::mousePressEvent(QMouseEvent *event)
{
    emit clicked();
}