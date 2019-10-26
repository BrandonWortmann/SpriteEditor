#ifndef DRAWFRAME_H
#define DRAWFRAME_H

#include <QWidget>

namespace Ui {
class DrawFrame;
}

class DrawFrame : public QWidget
{
    Q_OBJECT

public:
    explicit DrawFrame(QWidget *parent = nullptr);
    ~DrawFrame();

private:
    Ui::DrawFrame *ui;
};

#endif // DRAWFRAME_H
