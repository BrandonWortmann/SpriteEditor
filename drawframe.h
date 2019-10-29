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

private:
    DrawScene* drawScene;
};

#endif // DRAWFRAME_H
