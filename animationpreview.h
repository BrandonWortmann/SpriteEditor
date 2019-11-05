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
    void setupAnimationPreview();
    void setFrames(std::vector<QImage*>*);


public slots:
    void sliderMoved(int);
private:
    std::vector<QImage*>* frames;
    std::vector<QImage*>* tempFrames;
    size_t currFrame;
    AnimationPopup *animPop;
    void update();
    void displayFrames();

};

#endif // ANIMATIONPREVIEW_H
