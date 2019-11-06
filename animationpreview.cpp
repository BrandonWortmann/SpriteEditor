/************************************************
 *      A8 - Sprite Editor                      *
 *  Author: Wasted Potential                    *
 *  CS 3505                                     *
 *                                              *
 *  animationpreview.cpp, handles all the       *
 *  sprite animation                            *
 *                                              *
 ************************************************/

#include "animationpreview.h"
#include "ui_animationpreview.h"
#include <QAbstractSlider>
#include <QPixmap>
#include <QTimer>

/**
 * @brief AnimationPreview::AnimationPreview
 * Sets up the User Interface
 */
AnimationPreview::AnimationPreview(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AnimationPreview)
{
    ui->setupUi(this);
}

/**
 * @brief AnimationPreview::setupAnimationPreview
 * Sets up all the values needed to preview
 * the animation
 */
void AnimationPreview::setupAnimationPreview(QVector<QImage*> startingFrames)
{
    // Set up data
    animPop = new AnimationPopup();
    ui->displayLabel->setScaledContents(true);
    frames = startingFrames;
    update();

    // Connnections
    connect(ui->fpsSlider, &QAbstractSlider::sliderMoved,
            this, &AnimationPreview::sliderMoved);
    connect(ui->actualViewButton, &QPushButton::pressed,
            this, &AnimationPreview::actualViewPushed);
}

/**
 * @brief AnimationPreview::~AnimationPreview
 */
AnimationPreview::~AnimationPreview()
{
    delete ui;
}

/**
 * @brief AnimationPreview::sliderMoved
 * Displays the changed FPS number
 */
void AnimationPreview::sliderMoved(int value)
{
    ui->fpsLabel->setText("FPS: " + QString::number(value));
}

/**
 * @brief AnimationPreview::actualViewPushed
 * Displays the animation popup
 */
void AnimationPreview::actualViewPushed()
{
    if(animPop->isVisible())
    {
        return;
    }

    // Animation popup
    animPop->popupSetup(frames, ui->fpsSlider->value());
    animPop->show();
    animPop->update();
}

/**
 * @brief AnimationPreview::setFrames
 * Setter for getting the frames to
 * display in the animation preview
 */
void AnimationPreview::setFrames(QVector<QImage*> frameVector)
{
    frames = frameVector;
}

/**
 * @brief AnimationPreview::update
 * Updates the animation to get
 * the accurate frames that have
 * been changed
 */
void AnimationPreview::update()
{
    currFrame = 0;
    tempFrames = frames;
    QTimer::singleShot(5, this, &AnimationPreview::displayFrames);
}

/**
 * @brief AnimationPreview::displayFrames
 * Displays the frames with the given
 * fps from the user
 */
void AnimationPreview::displayFrames() {
    if(tempFrames != frames)
    {
        QTimer::singleShot(5, this, &AnimationPreview::update);
        return;
    }

    ui->displayLabel->setPixmap(QPixmap::fromImage(*tempFrames[currFrame]));
    currFrame++;
    if(currFrame == tempFrames.size())
    {
        QTimer::singleShot(int (1000.0 / ui->fpsLabel->text().split(" ")[1].toInt()), this, &AnimationPreview::update);
    }
    else
    {
        QTimer::singleShot(int (1000.0 / ui->fpsLabel->text().split(" ")[1].toInt()), this, &AnimationPreview::displayFrames);
    }
}
