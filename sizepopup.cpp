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
    ui->setupUi(this);
    QStringList sizeOptions = {"16x16","32x32","64x64", "128x128"};
    ui->comboBox->addItems(sizeOptions);




}

SizePopup::~SizePopup()
{
    delete ui;
}
