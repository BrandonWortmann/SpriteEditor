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
    QColor color(0, 0, 0, 0);
    startingImage->fill(color);
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
    connect(ui->dupFrameButton, &QPushButton::pressed,
            this, &FrameManager::duplicateFrame);
}

QVector<QImage*> FrameManager::getFrames() {
    return frames;
}

void FrameManager::setFrames(QVector<QImage*> newFrames) {

    for(int i = 0; i < frames.size(); i++)
       delete frames[i];

    for(int i = 0; i < newFrames.size(); i++)
        frames.push_back(newFrames[i]);
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
    QImage* newFrame = new QImage(frames[0]->size(), QImage::Format_ARGB32);
    QColor color(0, 0, 0, 0);
    newFrame->fill(color);
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

void FrameManager::duplicateFrame() {

    int size = frames[currFrame]->width();

    QImage *dupFrame = new QImage(QSize(size, size), QImage::Format_ARGB32);
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            QColor color = frames[currFrame]->pixelColor(i,j);
            dupFrame->setPixelColor(i, j, color);
        }
    }
    frames.push_back(dupFrame);
    currFrame = frames.size() - 1;
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

void FrameManager::update() {
    QImage blankImage(frames[0]->size(), QImage::Format_ARGB32);
    if(currFrame == 0 || currFrame == frames.size() - 1) {
        QColor newColor(0, 0, 0, 0);
        blankImage.fill(newColor);
    }
    if(currFrame != 0) {
        ui->prevLabel->setPixmap(QPixmap::fromImage(*frames[currFrame - 1]));
        ui->prevLabelNum->setText(QString::number(currFrame));
    }
    else {
        ui->prevLabelNum->setText("");
        ui->prevLabel->setPixmap(QPixmap::fromImage(blankImage));
    }

    if(currFrame < frames.size() - 1) {
        ui->nextLabel->setPixmap(QPixmap::fromImage(*frames[currFrame + 1]));
        ui->nextLabelNum->setText(QString::number(currFrame + 2));
    }
    else {
        ui->nextLabelNum->setText("");
        ui->nextLabel->setPixmap(QPixmap::fromImage(blankImage));
    }

    ui->currLabel->setPixmap(QPixmap::fromImage(*frames[currFrame]));
    ui->currLabelNum->setText(QString::number(currFrame + 1));
    QTimer::singleShot(50, this, &FrameManager::update);
}
