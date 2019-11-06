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
    void popupSetup(QVector<QImage*>, int);

private:
    Ui::AnimationPopup *ui;
    QVector<QImage*> frames;
    QVector<QImage*> tempFrames;
    int currFPS;
    int currFrame;
    void update();
    void displayFrames();
};

#endif // ANIMATIONPOPUP_H
