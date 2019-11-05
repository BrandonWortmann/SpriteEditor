#include "framemanager.h"
#include "ui_framemanager.h"
#include <QPixmap>
#include <QPushButton>
#include <QTimer>
#include <QVector>
#include <stdio.h>

using namespace std;
FrameManager::FrameManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FrameManager)
{
    ui->setupUi(this);
}

FrameManager::~FrameManager()
{
    delete ui;
}

void FrameManager::setupFrameManager()
{
    QImage* startingImage = new QImage(QSize(64, 64), QImage::Format_ARGB32);

    for(int i = 0; i < 64; i++) {
        for(int j =0; j < 64; j++) {
            QColor color(255, 255, 255, 255);
            startingImage->setPixelColor(i, j, color);
        }
    }
    frames.push_back(startingImage);
    currFrame = 0;
    ui->currLabelNum->setText("0");



    QImage* image1 = new QImage("../SpriteEditor/icons/goofy.png");
    QImage* image2 = new QImage("../SpriteEditor/icons/pencil.png");
    QImage* image3 = new QImage("../SpriteEditor/icons/papafranku.png");
    ui->prevLabel->setPixmap(QPixmap::fromImage(*image1));
    ui->prevLabel->setScaledContents(true);
    ui->currLabel->setPixmap(QPixmap::fromImage(*image2));
    ui->currLabel->setScaledContents(true);
    ui->nextLabel->setPixmap(QPixmap::fromImage(*image3));
    ui->nextLabel->setScaledContents(true);

    emit changeCurrFrame(startingImage);
    update();

    connect(ui->newFrameButton, &QPushButton::pressed,
            this, &FrameManager::addFrame);
    connect(ui->deleteFrameButton, &QPushButton::pressed,
            this, &FrameManager::deleteFrame);
    connect(ui->leftButton, &QPushButton::pressed,
            this, &FrameManager::moveLeft);
    connect(ui->rightButton, &QPushButton::pressed,
            this, &FrameManager::moveRight);
}

QVector<QImage*> FrameManager::getFrames() {
    return frames;
}

void FrameManager::setFrames(QVector<QImage*> newFrames) {
    frames = newFrames;
}

void FrameManager::setSize(int value) {
    for(int i = 0; i < frames.size(); i++) {
        QImage newImage = frames[i]->scaled(value, value, Qt::KeepAspectRatio);
        QImage* oldImage = frames[i];
        frames[i] = &newImage;
        delete oldImage;
    }

    emit changeCurrFrame(frames[currFrame]);
    emit changeFrameStructure(frames);
}

/*********
 * Slot
 * ******/

void FrameManager::addFrame()
{
    QImage* newFrame = new QImage(QSize(64, 64), QImage::Format_ARGB32);
    for(int i = 0; i < 64; i++) {
        for(int j =0; j < 64; j++) {
            QColor color(255, 255, 255, 255);
            newFrame->setPixelColor(i, j, color);
        }
    }
    frames.push_back(newFrame);
    currFrame = frames.size() - 1;
    emit changeCurrFrame(frames[currFrame]);
    emit changeFrameStructure(frames);
}

void FrameManager::deleteFrame()
{
    if(frames.size() == 1)
    {
        return;
    }

    frames.erase(frames.begin() + (int (currFrame)));
    if(currFrame != 0)
    {
        currFrame--;
    }

    emit changeCurrFrame(frames[currFrame]);
    emit changeFrameStructure(frames);
}

void FrameManager::moveLeft()
{
    if(currFrame == 0)
    {
        return;
    }

    currFrame--;
    emit changeCurrFrame(frames[currFrame]);
}

void FrameManager::moveRight()
{
    if(currFrame == frames.size() - 1) {
        return;
    }
    currFrame++;

    emit changeCurrFrame(frames[currFrame]);
}

//void FrameManager::sendCurrFrame()
//{
//    if(currFrame != 0) {
//        ui->prevLabel->setPixmap(QPixmap::fromImage(*frames[currFrame - 1]));
//        ui->prevLabelNum->setText(QString::number(currFrame));
//    }
//    else {
//        ui->prevLabelNum->setText("");
//    }

//    if(currFrame < frames.size() - 1) {
//        ui->nextLabel->setPixmap(QPixmap::fromImage(*frames[currFrame + 1]));
//        ui->nextLabelNum->setText(QString::number(currFrame + 2));
//    }
//    else {
//        ui->nextLabelNum->setText("");
//    }

//    ui->currLabel->setPixmap(QPixmap::fromImage(*frames[currFrame]));
//    ui->currLabelNum->setText(QString::number(currFrame + 1));

//    emit changeCurrFrame(frames[currFrame]);
//}

void FrameManager::update() {
    if(currFrame != 0) {
        ui->prevLabel->setPixmap(QPixmap::fromImage(*frames[currFrame - 1]));
        ui->prevLabelNum->setText(QString::number(currFrame));
    }
    else {
        ui->prevLabelNum->setText("");
    }

    if(currFrame < frames.size() - 1) {
        ui->nextLabel->setPixmap(QPixmap::fromImage(*frames[currFrame + 1]));
        ui->nextLabelNum->setText(QString::number(currFrame + 2));
    }
    else {
        ui->nextLabelNum->setText("");
    }

    ui->currLabel->setPixmap(QPixmap::fromImage(*frames[currFrame]));
    ui->currLabelNum->setText(QString::number(currFrame + 1));
    QTimer::singleShot(50, this, &FrameManager::update);
}
