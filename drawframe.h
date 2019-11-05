#ifndef DRAWFRAME_H
#define DRAWFRAME_H

#include <QWidget>
#include "drawscene.h"

namespace Ui {
class DrawFrame;
}

class DrawFrame : public QWidget
{
    Q_OBJECT

public:
    DrawFrame(QWidget *parent = nullptr);
    ~DrawFrame() override;
    Ui::DrawFrame *ui;
    void setupFrame();
    void setPencilSize(int);
    void setcolor(QColor);
    void zoom(bool);
    void gridToggle();
    void setFrame(QImage* frame);
    void setTool(int);
    DrawScene* drawScene;
};

#endif // DRAWFRAME_H
