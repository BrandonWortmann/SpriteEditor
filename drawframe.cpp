#include "drawframe.h"
#include "ui_drawframe.h"

DrawFrame::DrawFrame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DrawFrame)
{
    ui->setupUi(this);
}

DrawFrame::~DrawFrame()
{
    delete ui;
}
