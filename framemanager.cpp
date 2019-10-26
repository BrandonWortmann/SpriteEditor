#include "framemanager.h"
#include "ui_framemanager.h"

FrameManager::FrameManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FrameManager)
{
    ui->setupUi(this);
}

FrameManager::~FrameManager()
{
    delete ui;
}
