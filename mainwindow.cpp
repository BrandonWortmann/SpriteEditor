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
#include <QJsonObject>
#include <QJsonArray>
#include <QPalette>
#include <QByteArray>
#include <QBuffer>

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

    QPixmap pencilPix("../a8-sprite-editor-f19-Nordicade/icons/pencil.svg");
    QIcon pencilIcon;
    pencilIcon.addPixmap(pencilPix);
    toolBar->ui->pencilBtn->setIcon(pencilIcon);
    toolBar->ui->pencilBtn->setIconSize(QSize(30,30));
    QPixmap handPix("../a8-sprite-editor-f19-Nordicade/icons/hand.svg");
    QIcon handIcon;
    handIcon.addPixmap(handPix);
    toolBar->ui->handBtn->setIcon(handIcon);
    toolBar->ui->handBtn->setIconSize(QSize(30,30));
    QPixmap eraserPix("../a8-sprite-editor-f19-Nordicade/icons/eraser.svg");
    QIcon eraserIcon;
    eraserIcon.addPixmap(eraserPix);
    toolBar->ui->eraserBtn->setIcon(eraserIcon);
    toolBar->ui->eraserBtn->setIconSize(QSize(30,30));
    QPixmap bucketPix("../a8-sprite-editor-f19-Nordicade/icons/bucket.svg");
    QIcon bucketIcon;
    bucketIcon.addPixmap(bucketPix);
    toolBar->ui->bucketBtn->setIcon(bucketIcon);
    toolBar->ui->bucketBtn->setIconSize(QSize(30,30));
    QPixmap gridPix("../a8-sprite-editor-f19-Nordicade/icons/grid.svg");
    QIcon gridIcon;
    gridIcon.addPixmap(gridPix);
    toolBar->ui->gridBtn->setIcon(gridIcon);
    toolBar->ui->gridBtn->setIconSize(QSize(30,30));

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
    connect(frameManager, &FrameManager::changeCurrFrames, this, &MainWindow::changeCurrFrames);
    connect(frameManager, &FrameManager::changeFrameStructure, this, &MainWindow::changeFrameStructure);
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

// DrawFrame slots

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

// FrameManager slots

void MainWindow::changeCurrFrames(QImage* leftImage, QImage* midImage, QImage* rightImage) {
    if(leftImage) {
        frameManager->ui->prevLabel->setPixmap(QPixmap::fromImage(*leftImage));
        frameManager->ui->prevLabel->show();
    }
    else {
        frameManager->ui->prevLabel->hide();
    }

    if(rightImage) {
        frameManager->ui->nextLabel->show();
        frameManager->ui->nextLabel->setPixmap(QPixmap::fromImage(*rightImage));
    }
    else {
        frameManager->ui->currLabel->hide();
    }

    frameManager->ui->currLabel->setPixmap(QPixmap::fromImage(*midImage));
}

void MainWindow::changeFrameStructure(std::vector<QImage*>* frames) {

}

void MainWindow::newSprite()
{
    std::cout<<"new"<<std::endl;
}

void MainWindow::openSprite()
{
    std::cout<<"open"<<std::endl;

    QString fname = QFileDialog::getOpenFileName(this, tr("OpenSprite"), "", tr("Sprite Files (*.ssp)"));
    fileName = fname;
    std::string convert = fname.toStdString();
    QFile file(fname);
    QString allText;
    if(file.exists())
    {
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        allText = file.readAll();
        file.close();

        QJsonDocument jsonDoc = QJsonDocument::fromJson(allText.toUtf8());

        if(jsonDoc.isNull() || !jsonDoc.isObject())
        {
            //TODO - Popup for file error (wrong format)
            std::cout<<"ERROR - null"<<std::endl;
        }
        QJsonObject jsonObj = jsonDoc.object();
        if(jsonObj.isEmpty())
        {
            //TODO - Popup for file error (file empty)
            std::cout<<"ERROR - empty file"<<std::endl;
        }

        int size = jsonObj["height"].toInt();
        int numberOfFrames = jsonObj["numberOfFrames"].toInt();
        QJsonObject frames = jsonObj["frames"].toObject();

        QVector<QImage*> listOfFrames;

        for(int i = 0; i < numberOfFrames; i++)
        {
            QString frameNumber = "frame" + QString::number(i);
            QByteArray byteArr = frames[frameNumber].toString().toUtf8();
            QImage pixImage;
            pixImage.loadFromData(QByteArray::fromBase64(byteArr));
            listOfFrames.append(&pixImage);
        }
        //TODO - Drawscene/Drawframe method to send frame data
    }
}

void MainWindow::saveSprite()
{
    //temp variables
    std::cout<<"save"<<std::endl;
    int s = 4;
    QVector<QImage*> sample;

    QImage q;
    sample.append(&q);
    //temp variables (set size = real size)

    if(fileName.isNull() || fileName == "")
    {
        saveAsSprite();
    }
    int size = s;
    QJsonObject sprite;
    QJsonObject frames;

    for(int i = 0; i < sample.length(); i++)
    {
        QString frameNumber = "frame" + QString::number(i);
        QJsonArray jsonArr;
        frames[frameNumber] = jsonArr;
    }
    sprite["frames"] = frames;
    sprite["numberOfFrames"] = sample.length();
    sprite["width"] = size;
    sprite["height"] = size;


    QJsonDocument savedDoc(sprite);
    savedDoc.toJson(QJsonDocument::Indented);
    QFile saveFile(fileName);
    saveFile.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text);
    saveFile.write(savedDoc.toJson(QJsonDocument::Indented));

}

void MainWindow::saveAsSprite()
{
    std::cout<<"saveAs"<<std::endl;

    QString fname = QFileDialog::getSaveFileName(this, tr("OpenSprite"), "", tr("Sprite File (*.ssp)"));
    fileName = fname;

    saveSprite();

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
