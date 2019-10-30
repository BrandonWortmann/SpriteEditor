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
#include <QFileDialog>
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
    help = new HelpPopup;

    toolBar->ui->setupUi(ui->tbWidge);
    frameManager->ui->setupUi(ui->fmWidge);
    animationPreview->ui->setupUi(ui->apWidge);
    drawFrame->ui->setupUi(ui->dfWidge);
    drawFrame->setupFrame();

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
    connect(toolBar->ui->pSizeSlider, &QSlider::valueChanged, toolBar, &ToolBar::pencilSizeChanged);
    connect(toolBar, &ToolBar::setPencilSize, this, &MainWindow::setPencilSize);
    connect(ui->actionNew, &QAction::triggered, this, &MainWindow::newSprite);
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::openSprite);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::saveSprite);
    connect(ui->actionSaveAs, &QAction::triggered, this, &MainWindow::saveAsSprite);
    connect(ui->actionExport, &QAction::triggered, this, &MainWindow::exportSprite);
    connect(ui->actionClose, &QAction::triggered, this, &MainWindow::closeSprite);
    connect(ui->actionHelp, &QAction::triggered, this, &MainWindow::openHelpMenu);


}

MainWindow::~MainWindow()
{
    delete ui;
    delete toolBar;
    delete frameManager;
    delete animationPreview;
    delete drawFrame;
    delete help;
}

void MainWindow::setColor(QColor color)
{
    drawFrame->setcolor(color);
}

void MainWindow::setSize(int dimension)
{
    drawFrame->setSize(dimension);
}

void MainWindow::setTool(int tool)
{
    drawFrame->setTool(tool);
}

void MainWindow::toggleGrid()
{
    drawFrame->gridToggle();
}

void MainWindow::toggleZoom()
{
   // showZoom = !showZoom;
    //TODO: add zoom out button
}

void MainWindow::setPencilSize(int size)
{
    drawFrame->setPencilSize(size);
}

void MainWindow::newSprite()
{
    std::cout<<"new"<<std::endl;
}

void MainWindow::openSprite()
{
    std::cout<<"open"<<std::endl;

    QString filename = QFileDialog::getOpenFileName(this, tr("OpenSprite"), "", tr("Sprite Files (*.ssp)"));
    std::string convert = filename.toStdString();
    std::cout<<convert<<std::endl;
    //check if filename matches format (Json and sqare)

}

void MainWindow::saveSprite()
{
    std::cout<<"save"<<std::endl;
}

void MainWindow::saveAsSprite()
{
    std::cout<<"saveAs"<<std::endl;
}

void MainWindow::exportSprite()
{
    std::cout<<"export"<<std::endl;
}

void MainWindow::closeSprite()
{
    this->close();
}

void MainWindow::openHelpMenu()
{
    help->show();
}
