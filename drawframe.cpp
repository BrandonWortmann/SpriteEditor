#include "drawframe.h"
#include "ui_drawframe.h"
#include <QFileDialog>

DrawFrame::DrawFrame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DrawFrame)
{
    ui->setupUi(this);
}

void DrawFrame::setupFrame()
{
    drawScene = new DrawScene(this);
    ui->drawView->setScene(drawScene);
}

DrawFrame::~DrawFrame()
{
    delete ui;
}

void DrawFrame::setSize(int size)
{
 //TODO: Set size
}
void DrawFrame::setcolor(QColor color)
{
    drawScene->setColor(color);
}
void DrawFrame::setPencilSize(int size)
{
    //TODO: set pencil size
}
void DrawFrame::gridToggle()
{
    drawScene->gridToggle();
    drawScene->update();
}
void DrawFrame::setTool(int tool)
{
    //TODO: tool
}
void DrawFrame::zoom(bool zoom)
{
    //TODO: zoom

}
