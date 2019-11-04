#ifndef ANIMATIONPREVIEW_H
#define ANIMATIONPREVIEW_H

#include <QWidget>

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
};

#endif // ANIMATIONPREVIEW_H
