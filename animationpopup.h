#ifndef ANIMATIONPOPUP_H
#define ANIMATIONPOPUP_H

#include <QWidget>

namespace Ui {
class AnimationPopup;
}

class AnimationPopup : public QWidget
{
    Q_OBJECT

public:
    explicit AnimationPopup(QWidget *parent = nullptr);
    ~AnimationPopup();
    void setFrames(std::vector<QImage*>);

private:
    Ui::AnimationPopup *ui;
    std::vector<QImage*> frames;
};

#endif // ANIMATIONPOPUP_H
