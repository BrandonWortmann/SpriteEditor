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
};

#endif // ANIMATIONPREVIEW_H
