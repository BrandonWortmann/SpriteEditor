#include "animationpreview.h"
#include "ui_animationpreview.h"
#include <QAbstractSlider>
#include <QPixmap>
#include <QTimer>

AnimationPreview::AnimationPreview(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AnimationPreview)
{
    ui->setupUi(this);
}

void AnimationPreview::setupAnimationPreview(QVector<QImage*> startingFrames)
{
    animPop = new AnimationPopup();
    ui->displayLabel->setScaledContents(true);
    frames = startingFrames;
    update();

    connect(ui->fpsSlider, &QAbstractSlider::sliderMoved,
            this, &AnimationPreview::sliderMoved);
    connect(ui->actualViewButton, &QPushButton::pressed,
            this, &AnimationPreview::actualViewPushed);
}

AnimationPreview::~AnimationPreview()
{
    delete ui;
}


void AnimationPreview::sliderMoved(int value)
{
    ui->fpsLabel->setText("FPS: " + QString::number(value));
}

void AnimationPreview::actualViewPushed() {

    animPop->popupSetup(frames, ui->fpsSlider->value());
    animPop->show();
}

void AnimationPreview::setFrames(QVector<QImage*> frameVector)
{
    frames = frameVector;
}

void AnimationPreview::update()
{
    currFrame = 0;
    tempFrames = frames;
    QTimer::singleShot(5, this, &AnimationPreview::displayFrames);
}

void AnimationPreview::displayFrames() {
    ui->displayLabel->setPixmap(QPixmap::fromImage(*tempFrames[currFrame]));
    currFrame++;
    if(currFrame == tempFrames.size()) {
        QTimer::singleShot(int (1000.0 / ui->fpsLabel->text().split(" ")[1].toInt()), this, &AnimationPreview::update);
    }
    else {
        QTimer::singleShot(int (1000.0 / ui->fpsLabel->text().split(" ")[1].toInt()), this, &AnimationPreview::displayFrames);
    }
}
