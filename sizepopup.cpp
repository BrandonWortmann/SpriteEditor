#include "sizepopup.h"
#include "ui_sizepopup.h"
#include <QPushButton>
#include <QComboBox>
#include <iostream>
#include "toolbar.h"

SizePopup::SizePopup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SizePopup)
{
    const int defaultSizeIndex = 3;
    ui->setupUi(this);
    QStringList sizeOptions = {"4x4","16x16","32x32","64x64", "128x128"};
    ui->comboBox->addItems(sizeOptions);
    ui->comboBox->setCurrentIndex(defaultSizeIndex);

}

SizePopup::~SizePopup()
{
    delete ui;
}
