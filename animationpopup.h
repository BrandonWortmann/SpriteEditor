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
    void setFrames(std::vector<QImage*>);

private:
    Ui::AnimationPopup *ui;
    std::vector<QImage*> frames;

};

#endif // ANIMATIONPOPUP_H
