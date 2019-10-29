#include "mainwindow.h"
#include "toolbar.h"
#include "ui_mainwindow.h"
#include "ui_animationpreview.h"
#include "ui_drawframe.h"
#include "ui_framemanager.h"
#include "ui_toolbar.h"
#include <QDockWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QColor>
#include <iostream>
#include <QComboBox>

#include "ui_sizepopup.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    toolBar = new ToolBar;
    frameManager = new FrameManager;
    animationPreview = new AnimationPreview;
    drawFrame = new DrawFrame;

    toolBar->ui->setupUi(ui->tbWidge);
    frameManager->ui->setupUi(ui->fmWidge);
    animationPreview->ui->setupUi(ui->apWidge);
    drawFrame->ui->setupUi(ui->dfWidge);

    currDimension = 64;
    currColor.setRgb(0,0,0,0);
    currTool = 0;
    showGrid = false;
    showZoom = false;


    connect(toolBar->ui->colorBtn, &QPushButton::pressed, toolBar, &ToolBar::colorSelected);
    connect(toolBar, &ToolBar::setColor, this, &MainWindow::setColor);
    connect(toolBar->ui->sizeBtn, &QPushButton::pressed, toolBar, &ToolBar::openSize);
    connect(toolBar, &ToolBar::setSize, this, &MainWindow::setSize);
    connect(toolBar->ui->pencilBtn, &QPushButton::pressed, toolBar, &ToolBar::pencilSelected);
    connect(toolBar, &ToolBar::setTool, this, &MainWindow::setTool);
    connect(toolBar->ui->eraserBtn, &QPushButton::pressed, toolBar, &ToolBar::eraserSelected);
    connect(toolBar->ui->handBtn, &QPushButton::pressed, toolBar, &ToolBar::handSelected);
    connect(toolBar->ui->bucketBtn, &QPushButton::pressed, toolBar, &ToolBar::bucketSelected);
    connect(toolBar->ui->gridBtn, &QPushButton::pressed, toolBar, &ToolBar::gridSelected);
    connect(toolBar, &ToolBar::toggleGrid, this, &MainWindow::toggleGrid);
    connect(toolBar->ui->zoomBtn, &QPushButton::pressed, toolBar, &ToolBar::zoomSelected);
    connect(toolBar, &ToolBar::toggleZoom, this, &MainWindow::toggleZoom);

    // DrawFrame stuff
    drawFrame->setupFrame();


}

MainWindow::~MainWindow()
{
    delete ui;
    delete toolBar;
    delete frameManager;
    delete animationPreview;
    delete drawFrame;
}

void MainWindow::setColor(QColor color){
    currColor = color;
}

void MainWindow::setSize(int dimension){
    currDimension = dimension;
}

void MainWindow::setTool(int tool){
    currTool = tool;
}

void MainWindow::toggleGrid(){
    showGrid = !showGrid;
}

void MainWindow::toggleZoom(){
    showZoom = !showZoom;

}
