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
    ~DrawFrame();
    Ui::DrawFrame *ui;
    void setupFrame();
    void setSize(int);
    void setPencilSize(int);
   // void setTool(int);
    void setcolor(QColor);
    void zoom(bool);
    void gridToggle();

private:
    DrawScene* drawScene;

public slots:
    void setTool(int);
};

#endif // DRAWFRAME_H
