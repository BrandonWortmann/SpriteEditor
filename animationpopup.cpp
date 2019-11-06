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

/**
 * @brief AnimationPopup::AnimationPopup
 * Sets up the User Interface for the
 * animation popup
 */
AnimationPopup::AnimationPopup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AnimationPopup)
{
    ui->setupUi(this);
}

/**
 * @brief AnimationPopup::~AnimationPopup
 */
AnimationPopup::~AnimationPopup()
{
    delete ui;
}

/**
 * @brief AnimationPopup::popupSetup
 * Sets up the values for the animation popup
 */
void AnimationPopup::popupSetup(QVector<QImage*> newFrames, int fps)
{
    frames = newFrames;
    currFPS = fps;
}

/**
 * @brief AnimationPopup::update
 * Updates the animation popup
 * to have the accurate frames
 * being displayed
 */
void AnimationPopup::update()
{
    currFrame = 0;
    tempFrames = frames;
    QTimer::singleShot(5, this, &AnimationPopup::displayFrames);
}

/**
 * @brief AnimationPopup::displayFrames
 * Displays the animation popup
 */
void AnimationPopup::displayFrames()
{
    if(!this->isVisible())
    {
        return;
    }

    ui->popupLabel->setPixmap(QPixmap::fromImage(*tempFrames[currFrame]));
    currFrame++;

    if(currFrame == tempFrames.size())
    {
        QTimer::singleShot(int (1000.0 / currFPS), this, &AnimationPopup::update);
    }
    else
    {
        QTimer::singleShot(int (1000.0 / currFPS), this, &AnimationPopup::displayFrames);
    }
}
