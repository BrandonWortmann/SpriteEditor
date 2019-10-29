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
