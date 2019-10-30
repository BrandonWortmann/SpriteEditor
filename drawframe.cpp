#include "drawframe.h"
#include "ui_drawframe.h"

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
    //TODO: SetColor
}
void DrawFrame::setPencilSize(int size)
{
    //TODO: set pencil size
}
void DrawFrame::gridToggle()
{
    //TODO: toogle grid
}
void DrawFrame::setTool(int tool)
{
    //TODO: tool
}
void DrawFrame::zoom(bool zoom)
{
    //TODO: zoom
}
