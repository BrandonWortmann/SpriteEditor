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
#include <QJsonDocument>
#include <QJsonArray>
#include <QPalette>

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


    QColor black(0,0,0,255);
    toolBar->setBtnColor(black);

    // showing images for frames in qt
    frameManager->ui->currLabel->setText("Thotto begonno");


    QImage* image1 = new QImage("../SpriteEditor/icons/goofy.png");
    QImage* image2 = new QImage("../SpriteEditor/icons/pencil.png");
    QImage* image3 = new QImage("../SpriteEditor/icons/papafranku.png");
    frameManager->ui->prevLabel->setPixmap(QPixmap::fromImage(*image1));
    frameManager->ui->prevLabel->setScaledContents(true);
    frameManager->ui->currLabel->setPixmap(QPixmap::fromImage(*image2));
    frameManager->ui->currLabel->setScaledContents(true);
    frameManager->ui->nextLabel->setPixmap(QPixmap::fromImage(*image3));
    frameManager->ui->nextLabel->setScaledContents(true);


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
    connect(toolBar->ui->zoomInBtn, &QPushButton::pressed, toolBar, &ToolBar::zoomInSelected);
    connect(toolBar->ui->zoomOutBtn, &QPushButton::pressed, toolBar, &ToolBar::zoomOutSelected);
    connect(toolBar, &ToolBar::toggleZoomIn, this, &MainWindow::toggleZoomIn);
    connect(toolBar, &ToolBar::toggleZoomOut, this, &MainWindow::toggleZoomOut);
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
    toolBar->ui->pencilBtn->setChecked(false);
    toolBar->ui->handBtn->setChecked(false);
    toolBar->ui->eraserBtn->setChecked(false);
    toolBar->ui->bucketBtn->setChecked(false);

    drawFrame->setTool(tool);
}

void MainWindow::toggleGrid()
{
    drawFrame->gridToggle();
}

void MainWindow::toggleZoomIn()
{
    drawFrame->zoom(true);
    std::cout<< "zoom in";
}

void MainWindow::toggleZoomOut()
{
    drawFrame->zoom(false);
    std::cout<< "zoom out";
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
    QFile file(filename);
    QString allText;
    if(file.exists())
    {
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        allText = file.readAll();
        file.close();

        QJsonDocument jsonDoc = QJsonDocument::fromJson(allText.toUtf8());

        if(jsonDoc.isNull()){
            std::cout<<"jsonDoc is null"<<std::endl;
        }

        QJsonArray jsonArr = jsonDoc.array();

        for(int i = 0; i < jsonArr.size(); i++)
        {
         QJsonValue val = jsonArr.at(i);
        }
    }
    else{
        std::cout<<"File does not exist." << std::endl;
    }
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
