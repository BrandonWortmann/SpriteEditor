#include "animationpreview.h"
#include "ui_animationpreview.h"

AnimationPreview::AnimationPreview(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AnimationPreview)
{
    ui->setupUi(this);
}

AnimationPreview::~AnimationPreview()
{
    delete ui;
}
