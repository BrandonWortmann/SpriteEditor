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
