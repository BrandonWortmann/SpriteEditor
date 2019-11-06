/************************************************
 *      A8 - Sprite Editor                      *
 *  Author: Wasted Potential                    *
 *  CS 3505                                     *
 *                                              *
 *  mainwindow.cpp                              *
 *  UI and view thatestablishes connections.    *
 *                                              *
 ************************************************/


#include "mainwindow.h"
#include "toolbar.h"
#include "gif.h"
#include "ui_mainwindow.h"
#include "ui_animationpreview.h"
#include "ui_drawframe.h"
#include "ui_framemanager.h"
#include "ui_toolbar.h"
#include "ui_sizepopup.h"
#include <QPushButton>
#include <QColor>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonArray>
#include <QPalette>
#include <QJsonObject>
#include <QMessageBox>
#include <QCloseEvent>
#include <string>

/**
 * @brief MainWindow::MainWindow
 * Initializes all necessary values,
 * and establishes connections
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Instantiating objects to work with
    toolBar = new ToolBar;
    frameManager = new FrameManager;
    animationPreview = new AnimationPreview;
    drawFrame = new DrawFrame;
    help = new HelpPopup;

    // Setting up the proper UI's to the widgets
    toolBar->ui->setupUi(ui->tbWidge);
    frameManager->ui->setupUi(ui->fmWidge);
    animationPreview->ui->setupUi(ui->apWidge);
    drawFrame->ui->setupUi(ui->dfWidge);
    drawFrame->setupFrame();

    QColor black(255,0,0,0);
    toolBar->setBtnColor(black);

    // Showing images for frames in qt
    frameManager->setupFrameManager();
    animationPreview->setupAnimationPreview(frameManager->getFrames());
    drawFrame->setFrame(frameManager->getFrames()[0]);

    // Assigning toolbar images to buttons
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

    isSaved = true;
    size = 64;

    // Connections between mainwindow
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
    connect(frameManager, &FrameManager::changeCurrFrame, this, &MainWindow::changeCurrFrame);
    connect(frameManager, &FrameManager::changeFrameStructure, this, &MainWindow::changeFrameStructure);
    connect(toolBar, &ToolBar::setPencilSize, this, &MainWindow::setPencilSize);
    connect(ui->actionNew, &QAction::triggered, this, &MainWindow::newSprite);
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::openSprite);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::saveSprite);
    connect(ui->actionSaveAs, &QAction::triggered, this, &MainWindow::saveAsSprite);
    connect(ui->actionExport, &QAction::triggered, this, &MainWindow::exportSprite);
    connect(ui->actionClose, &QAction::triggered, this, &MainWindow::closeSprite);
    connect(ui->actionHelp, &QAction::triggered, this, &MainWindow::openHelpMenu);
    connect(drawFrame->drawScene, &DrawScene::setSaved, this, &MainWindow::setSaved);
}

/**
 * @brief MainWindow::~MainWindow
 * Removes all heap allocated memory
 */
MainWindow::~MainWindow()
{
    delete ui;
    delete toolBar;
    delete frameManager;
    delete animationPreview;
    delete drawFrame;
    delete help;
}

/**
 * @brief MainWindow::setColor
 * DrawFrame slot
 * Sets the color of the pencil
 */
void MainWindow::setColor(QColor color)
{
    drawFrame->setcolor(color);
}

/**
 * @brief MainWindow::setSize
 * DrawFrame slot
 * Sets the size of the window dimension
 */
void MainWindow::setSize(int dimension)
{
    size = uint(dimension);
    frameManager->setSize(dimension);
}

/**
 * @brief MainWindow::setTool
 * DrawFrame slot
 * Sets the tool picked by the user
 */
void MainWindow::setTool(int tool)
{
    toolBar->ui->pencilBtn->setChecked(false);
    toolBar->ui->handBtn->setChecked(false);
    toolBar->ui->eraserBtn->setChecked(false);
    toolBar->ui->bucketBtn->setChecked(false);
    drawFrame->setTool(tool);
}

/**
 * @brief MainWindow::toggleGrid
 * DrawFrame slot
 * Notifies the DrawFrame when the grid has been picked
 */
void MainWindow::toggleGrid()
{
    drawFrame->gridToggle();
}

/**
 * @brief MainWindow::toggleZoomIn
 * DrawFrame slot
 * Notifies the DrawFrame when the zoom
 * in has been picked
 */
void MainWindow::toggleZoomIn()
{
    drawFrame->zoom(true);
}

/**
 * @brief MainWindow::toggleZoomOut
 * DrawFrame slot
 * Notifies the DrawFrame when the zoom
 * out has been picked
 */
void MainWindow::toggleZoomOut()
{
    drawFrame->zoom(false);
}

/**
 * @brief MainWindow::setPencilSize
 * DrawFrame slot
 * Sets the pencil sizes
 */
void MainWindow::setPencilSize(int size)
{
    drawFrame->setPencilSize(size);
}


/**
 * @brief MainWindow::changeCurrFrame
 * FrameManager slot
 * Changes the current frame that is displayed
 */
void MainWindow::changeCurrFrame(QImage* newFrame) {
    drawFrame->setFrame(newFrame);
}

/**
 * @brief MainWindow::changeFrameStructure
 * FrameManager slot
 * Changes the frame structure in the MainWindows
 */
void MainWindow::changeFrameStructure(QVector<QImage*> frames) {
    animationPreview->setFrames(frames);
}

/**
 * @brief MainWindow::newSprite
 * Creates a new sprite. Gives the
 * user a blank canvas
 */
void MainWindow::newSprite()
{
    if(!isSaved)
    {
        // Saving dialog box
        QMessageBox warning;
        warning.setStandardButtons(QMessageBox::Save | QMessageBox::No);
        warning.setInformativeText("Unsaved Changes. Would you like to save?");
        int ret = warning.exec();

        if(ret == QMessageBox::Save)
        {
            saveSprite();
        }
    }

    // New fileName needs to be chosen
    fileName = "";

    // New frames, fills frame to white
    QVector<QImage*> pic;
    QImage *img = new QImage(QSize(64, 64), QImage::Format_ARGB32);
    QColor color(0, 0, 0, 0);
    for (int i = 0; i < 64; i++)
    {
        for (int j = 0; j < 64; j++)
        {
            img->setPixelColor(i, j, color);
        }
    }

    pic.append(img);
    frameManager->setFrames(pic);
}

/**
 * @brief MainWindow::openSprite
 * Opens a stored sprite. Popup
 * that asks the user to select
 * the .ssp file
 */
void MainWindow::openSprite()
{
    // Asks the user to select a .ssp file
    QString fname = QFileDialog::getOpenFileName(this, tr("OpenSprite"), "", tr("Sprite Files (*.ssp)"));
    fileName = fname;
    QFile file(fname);
    QString allText;
    QMessageBox errorMsg;

    if(file.exists())
    {
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        allText = file.readAll();
        file.close();

        // Converting to a Json Document and verifying a legit document
        QJsonDocument jsonDoc = QJsonDocument::fromJson(allText.toUtf8());
        if(jsonDoc.isNull() || !jsonDoc.isObject())
        {
            errorMsg.setInformativeText("File selected does not match format.");
            errorMsg.exec();
            return;
        }

        // Converting to a Json Object and veriying a legit Json Object
        QJsonObject jsonObj = jsonDoc.object();
        if(jsonObj.isEmpty())
        {
            errorMsg.setInformativeText("file selected is empty.");
            errorMsg.exec();
            return;
        }

        // Storing necessary values from the Json
        size = uint(jsonObj["height"].toInt());
        int numberOfFrames = jsonObj["numberOfFrames"].toInt();
        QJsonObject frames = jsonObj["frames"].toObject();

        // Acquiring necessary data from the Json to create a QImage
        QVector<QImage*> sprite;
        for(int frameNum = 0; frameNum < numberOfFrames; frameNum++)
        {
            QString frameNumber = "frame" + QString::number(frameNum);
            QJsonArray overallArr = frames[frameNumber].toArray();
            QImage* img = new QImage(QSize(int(size), int(size)), QImage::Format_ARGB32);
            for(int i = 0; i < int(size); i++)
            {
                QJsonArray rowArr = overallArr.at(i).toArray();
                for(int j = 0; j < int(size); j++)
                {
                    // Exctrating RGBA values
                    QJsonArray rgbaValues = rowArr.at(j).toArray();
                    int red = rgbaValues.at(0).toInt();
                    int green = rgbaValues.at(1).toInt();
                    int blue = rgbaValues.at(2).toInt();
                    int alpha = rgbaValues.at(3).toInt();

                    // Setting Pixel Color
                    QColor color(red, green, blue, alpha);
                    img->setPixelColor(j, i, color);
                }
            }
            sprite.append(img);
        }
        frameManager->setFrames(sprite);
    }
}

/**
 * @brief MainWindow::saveSprite
 * Saving the current sprite
 * The user should have already
 * picked a file saving location.
 * Saves to the same file
 */
void MainWindow::saveSprite()
{
    if(fileName.isNull() || fileName == "")
    {
        saveAsSprite();
    }

    QJsonObject sprite;
    QJsonObject frames;
    QVector<QImage*> imgVect = frameManager->getFrames();

    // Itterating over all the frames to store pixel RGBA values
    for(int frameNum = 0; frameNum < imgVect.length(); frameNum++)
    {
        QJsonArray overallArray;
        QString frameNumber = "frame" + QString::number(frameNum);
        QJsonArray rowArr;
        QVector<uint8_t> pixelVect(int(size)*4);
        for(int i = 0; i < int(size); i++)
        {
            QJsonArray colArray;
            for(int j = 0; j < int(size); j++)
            {
                QImage *img = imgVect.at(frameNum);
                QColor color = img->pixelColor(j,i);
                QJsonArray rgbaValues;

                rgbaValues.append(QJsonValue(color.red()));
                rgbaValues.append(QJsonValue(color.green()));
                rgbaValues.append(QJsonValue(color.blue()));
                rgbaValues.append(QJsonValue(color.alpha()));

                pixelVect.append(static_cast<uint8_t>(color.red()));
                pixelVect.append(static_cast<uint8_t>(color.green()));
                pixelVect.append(static_cast<uint8_t>(color.blue()));
                pixelVect.append(static_cast<uint8_t>(color.alpha()));

                colArray.append(rgbaValues);
            }
            overallArray.append(colArray);
        }

        pixelList.append(pixelVect);
        frames[frameNumber] = overallArray;
    }

    // Storing to Json Object
    sprite["frames"] = frames;
    sprite["numberOfFrames"] = imgVect.length();
    sprite["width"] = int(size);
    sprite["height"] = int(size);

    // Storing to a Json Document
    QJsonDocument savedDoc(sprite);
    savedDoc.toJson(QJsonDocument::Indented);

    // Saving the File
    QFile saveFile(fileName);
    saveFile.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text);
    saveFile.write(savedDoc.toJson(QJsonDocument::Indented));
    setSaved(true);
}

/**
 * @brief MainWindow::saveAsSprite
 * The user picks a file location
 * and a json .ssp file is created
 */
void MainWindow::saveAsSprite()
{
    QString fname = QFileDialog::getSaveFileName(this, tr("OpenSprite"), "", tr("Sprite File (*.ssp)"));
    if(!fname.isNull() || fname != "")
    {
        // Adding extension if the user does not add one
        std::string filePath = fname.toStdString();
        filePath = filePath.substr(filePath.length() - 3, filePath.length());

        if(filePath != "ssp")
        {
            QString ext = ".ssp";
            fname = fname + ext;
        }

        fileName = fname;
        saveSprite();
    }
}

/**
 * @brief MainWindow::exportSprite
 * Saves the current file and exports
 * it to a .gif format. File is exported
 * to the same location as the .ssp file
 */
void MainWindow::exportSprite()
{
    saveSprite();

    // GifWriter set up
    GifWriter g;
    std::string stringFileName = fileName.toStdString();
    stringFileName = stringFileName.substr(0,stringFileName.length() - 3);
    stringFileName.append("gif");
    const char* charFileName = stringFileName.c_str();

    // Constructing and saving the .gif file
    GifBegin(&g, charFileName, size, size, 50);
    for(int i = 0; i < pixelList.length(); i++)
    {
        GifWriteFrame(&g, pixelList.at(i).data(), size, size, 50);
    }
    GifEnd(&g);
}

/**
 * @brief MainWindow::closeSprite
 * Closes the sprite editor
 */
void MainWindow::closeSprite()
{

    this->close();
}

/**
 * @brief MainWindow::openHelpMenu
 * When called this method will
 * open the helpMenu popup
 */
void MainWindow::openHelpMenu()
{
    help->show();
}

/**
 * @brief MainWindow::setSaved
 * Setter for isSaved boolean
 * Documents whether the current
 * sprite has been recently saved
 */
void MainWindow::setSaved(bool saved)
{
    isSaved = saved;
}

/**
 * @brief MainWindow::closeEvent
 * Overrides the close event
 * and asks the user if they
 * have any unsaved changes
 */
void MainWindow::closeEvent(QCloseEvent *event)
{
    if(!isSaved)
    {
        QMessageBox warning;
        warning.setStandardButtons(QMessageBox::Save | QMessageBox::No);
        warning.setInformativeText("Unsaved Changes, would you like to save?");
        int ret = warning.exec();

        if(ret == QMessageBox::Save)
        {
            saveSprite();
        }
        event->accept();
    }
}
