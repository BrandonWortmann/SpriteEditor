#ifndef ANIMATIONPREVIEW_H
#define ANIMATIONPREVIEW_H

#include <QWidget>
#include "animationpopup.h"

namespace Ui {
class AnimationPreview;
}

class AnimationPreview : public QWidget
{
    Q_OBJECT

public:
    explicit AnimationPreview(QWidget *parent = nullptr);
    ~AnimationPreview();
    Ui::AnimationPreview *ui;
    void setupAnimationPreview(QVector<QImage*>);
    void setFrames(QVector<QImage*>);


public slots:
    void sliderMoved(int);
private:
    QVector<QImage*> frames;
    QVector<QImage*> tempFrames;
    int currFrame;
    AnimationPopup *animPop;
    void update();
    void displayFrames();

};

#endif // ANIMATIONPREVIEW_H
