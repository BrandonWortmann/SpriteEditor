#include "framemanager.h"
#include "ui_framemanager.h"
#include <QPixmap>

FrameManager::FrameManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FrameManager)
{
    ui->setupUi(this);
//    QImage* image1 = new QImage();
//    image1->load("goofy.png");
//    ui->currLabel->setPixmap(QPixmap::fromImage(*image1));
//    ui->currLabel->show();
//    ui->nextLabel->setText("Thotto Begonno");
//    ui->nextLabel->show();
//    frames.push_back(new QImage());

    QImage* startingImage = new QImage();
    frames.push_back(startingImage);

    changeCurrFrame(startingImage);


}

FrameManager::~FrameManager()
{
    delete ui;
}
