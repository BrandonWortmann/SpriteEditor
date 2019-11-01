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
    //drawScene->setSize(size);
    //drawScene->update();
}
void DrawFrame::setcolor(QColor color)
{
    drawScene->setColor(color);
}
void DrawFrame::setPencilSize(int size)
{
    drawScene->setPencilSize(size);
}
void DrawFrame::gridToggle()
{
    drawScene->gridToggle();
    drawScene->update();
}
void DrawFrame::setTool(int tool)
{
    drawScene->setTool(tool);
    setCursor((Qt::CursorShape::IBeamCursor));
    if(tool == 1)
    {
        setCursor(Qt::CursorShape::OpenHandCursor);
    }
}
void DrawFrame::zoom(bool zoom)
{
    drawScene->zoomScene(zoom);
    drawScene->update();
}

void DrawFrame::setFrame(QImage* frame)
{

}
