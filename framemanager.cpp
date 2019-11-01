#include "framemanager.h"
#include "ui_framemanager.h"
#include <QPixmap>
#include <QPushButton>
#include <stdio.h>

using namespace std;
FrameManager::FrameManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FrameManager)
{
    ui->setupUi(this);

    QImage* startingImage = new QImage();
    frames.push_back(startingImage);

    changeCurrFrames(nullptr, startingImage, nullptr);

    connect(ui->newFrameButton, &QPushButton::pressed,
            this, &FrameManager::addFrame);
    connect(ui->deleteFrameButton, &QPushButton::pressed,
            this, &FrameManager::deleteFrame);
    connect(ui->leftButton, &QPushButton::pressed,
            this, &FrameManager::moveLeft);
    connect(ui->rightButton, &QPushButton::pressed,
            this, &FrameManager::moveRight);
}

FrameManager::~FrameManager()
{
    delete ui;
}

/*********
 * Slot
 * ******/

void FrameManager::addFrame() {
    QImage* newFrame = new QImage();
    frames.push_back(newFrame);
    currFrame = frames.size() - 1;
    sendCurrFrames();
    emit changeFrameStructure(&frames);
    // TODO : move view to end
}

void FrameManager::deleteFrame() {
    if(frames.size() == 1) {
        return;
    }

    frames.erase(frames.begin() + ((int) currFrame));
    if(currFrame != 0) {
        currFrame--;
    }

    sendCurrFrames();
    emit changeFrameStructure(&frames);
}

void FrameManager::moveLeft() {
    if(currFrame == 0) {
        return;
    }

    currFrame--;
    sendCurrFrames();
}

void FrameManager::moveRight() {
    if(currFrame == frames.size() - 1) {
        return;
    }
    currFrame++;

    sendCurrFrames();
}

void FrameManager::sendCurrFrames() {

    QImage* leftFrame = nullptr;
    QImage* rightFrame = nullptr;

    if(currFrame != 0) {
        leftFrame = frames[currFrame - 1];
    }

    if(currFrame < frames.size() - 1) {
        rightFrame = frames[currFrame + 1];
    }

    emit changeCurrFrames(leftFrame, frames[currFrame], rightFrame);
}
