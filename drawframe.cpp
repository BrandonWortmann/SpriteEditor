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
    ui->drawView->setCursor(Qt::CursorShape::CrossCursor);
}

DrawFrame::~DrawFrame()
{
    delete ui;
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
    if(tool == 1)
    {
        ui->drawView->setCursor(Qt::CursorShape::OpenHandCursor);
    }
    else
    {
        ui->drawView->setCursor(Qt::CursorShape::CrossCursor);
    }
}
void DrawFrame::zoom(bool zoom)
{
    drawScene->zoomScene(zoom);
    drawScene->update();
}

void DrawFrame::setFrame(QImage* frame)
{
    drawScene->setFrame(frame);
    drawScene->update();
}
