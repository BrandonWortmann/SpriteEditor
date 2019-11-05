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

void AnimationPreview::setupAnimationPreview()
{
    animPop = new AnimationPopup();
    ui->displayLabel->setScaledContents(true);

    connect(ui->fpsSlider, &QAbstractSlider::sliderMoved,
            this, &AnimationPreview::sliderMoved);
}

AnimationPreview::~AnimationPreview()
{
    delete ui;
}


void AnimationPreview::sliderMoved(int value)
{
    ui->fpsLabel->setText("FPS: " + QString::number(value));
}

void AnimationPreview::setFrames(std::vector<QImage*>* frameVector)
{
    frames = frameVector;
}

void AnimationPreview::update()
{

    currFrame = 0;
    tempFrames = frames;
    QTimer::singleShot(5, this, &AnimationPreview::displayFrames);

//    while(true) {
//        std::vector<QImage*>* tempFrames = frames;
//        while(tempFrames == frames) {
//            for(size_t i = 0; i < tempFrames->size(); i++) {
//                ui->displayLabel->setPixmap(QPixmap::fromImage(*((*tempFrames)[i])));

//            }
//        }
//    }
}

void AnimationPreview::displayFrames() {
    ui->displayLabel->setPixmap(QPixmap::fromImage(*((*tempFrames)[currFrame])));
    currFrame++;
    if(currFrame == tempFrames->size()) {
        QTimer::singleShot(5, this, &AnimationPreview::update);
    }
    else {
        QTimer::singleShot(int (1000.0 / ui->fpsLabel->text().split(" ")[1].toInt()), this, &AnimationPreview::displayFrames);
    }
}
