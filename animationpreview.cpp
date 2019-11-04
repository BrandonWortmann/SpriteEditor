#include "animationpreview.h"
#include "ui_animationpreview.h"
#include <QAbstractSlider>

AnimationPreview::AnimationPreview(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AnimationPreview)
{
    ui->setupUi(this);
}

void AnimationPreview::setupAnimationPreview() {
    connect(ui->fpsSlider, &QAbstractSlider::sliderMoved,
            this, &AnimationPreview::sliderMoved);

}

AnimationPreview::~AnimationPreview()
{
    delete ui;
}


void AnimationPreview::sliderMoved(int value) {
    ui->fpsLabel->setText("FPS: " + QString::number(value));
}

void AnimationPreview::setFrames(std::vector<QImage*>* frameVector) {
    frames = frameVector;
}
