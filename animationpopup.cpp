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

void AnimationPopup::setFrames(std::vector<QImage*> newFrames) {
    frames = newFrames;
}
