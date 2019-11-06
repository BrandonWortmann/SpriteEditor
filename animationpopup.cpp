/************************************************
 *      A8 - Sprite Editor                      *
 *  Author: Wasted Potential                    *
 *  CS 3505                                     *
 *                                              *
 *  animationpopup.cpp, animation popup window  *
 *                                              *
 ************************************************/

#include "animationpopup.h"
#include "ui_animationpopup.h"
#include <QTimer>

AnimationPopup::AnimationPopup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AnimationPopup)
{
    ui->setupUi(this);
}

AnimationPopup::~AnimationPopup()
{
    delete ui;
}

void AnimationPopup::popupSetup(QVector<QImage*> newFrames, int fps) {
    frames = newFrames;
    currFPS = fps;
    update();
}

void AnimationPopup::update()
{
    currFrame = 0;
    tempFrames = frames;
    QTimer::singleShot(5, this, &AnimationPopup::displayFrames);
}

void AnimationPopup::displayFrames() {
   ui->popupLabel->setPixmap(QPixmap::fromImage(*tempFrames[currFrame]));
    currFrame++;
    if(currFrame == tempFrames.size()) {
        QTimer::singleShot(int (1000.0 / currFPS/*ui->fpsLabel->text().split(" ")[1].toInt()*/), this, &AnimationPopup::update);
    }
    else {
        QTimer::singleShot(int (1000.0 / currFPS/*ui->fpsLabel->text().split(" ")[1].toInt()*/), this, &AnimationPopup::displayFrames);
    }
}
