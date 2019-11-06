/************************************************
 *      A8 - Sprite Editor                      *
 *  Author: Wasted Potential                    *
 *  CS 3505                                     *
 *                                              *
 *  header file for AnimationPopup              *
 *                                              *
 ************************************************/

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
    void update();

private:
    Ui::AnimationPopup *ui;
    QVector<QImage*> frames;
    QVector<QImage*> tempFrames;
    int currFPS;
    int currFrame;
    void displayFrames();
};

#endif // ANIMATIONPOPUP_H
