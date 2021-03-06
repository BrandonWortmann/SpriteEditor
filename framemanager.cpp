/************************************************
 *      A8 - Sprite Editor                      *
 *  Author: Wasted Potential                    *
 *  CS 3505                                     *
 *                                              *
 *  framemanager.cpp, manages the sprite        *
 *  frames. Central hub for frame storage       *
 *                                              *
 ************************************************/

#include "framemanager.h"
#include "ui_framemanager.h"
#include <QPixmap>
#include <QPushButton>
#include <QTimer>
#include <QVector>
#include <stdio.h>

using namespace std;

/**
 * @brief FrameManager::FrameManager
 * Sets up the UI
 */
FrameManager::FrameManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FrameManager)
{
    ui->setupUi(this);
}

/**
 * @brief FrameManager::~FrameManager
 * Deletes UI
 */
FrameManager::~FrameManager()
{
    delete ui;
}

/**
 * @brief FrameManager::setupFrameManager
 * Sets up all the functionality for the
 * frameManager. Frame color, and connections
 */
void FrameManager::setupFrameManager()
{
    // Intial image set to transperant background
    QImage* startingImage = new QImage(QSize(64, 64), QImage::Format_ARGB32);
    QColor color(0, 0, 0, 0);
    startingImage->fill(color);
    frames.push_back(startingImage);
    currFrame = 0;
    ui->currLabelNum->setText("0");

    // Sends the current frame to DrawFrame
    emit changeCurrFrame(startingImage);
    update();

    // Connection for actions when a button is pushed
    connect(ui->newFrameButton, &QPushButton::pressed,
            this, &FrameManager::addFrame);
    connect(ui->deleteFrameButton, &QPushButton::pressed,
            this, &FrameManager::deleteFrame);
    connect(ui->leftButton, &QPushButton::pressed,
            this, &FrameManager::moveLeft);
    connect(ui->rightButton, &QPushButton::pressed,
            this, &FrameManager::moveRight);
    connect(ui->dupFrameButton, &QPushButton::pressed,
            this, &FrameManager::duplicateFrame);
}

/**
 * @brief FrameManager::getFrames
 * Getter for the QVector of frames
 */
QVector<QImage*> FrameManager::getFrames()
{
    return frames;
}

/**
 * @brief FrameManager::setFrames
 * Sets the new frames given, into the
 * the frames being used by all
 */
void FrameManager::setFrames(QVector<QImage*> newFrames)
{
    // Deletes the old frame pointers
    int origSize = frames.size();
    for(int i = 0; i < origSize; i++)
    {
       QImage* oldFrame = frames[0];
       frames.remove(0);
       delete oldFrame;
    }

    // Adds the new frames
    for(int i = 0; i < newFrames.size(); i++)
    {
        frames.push_back(newFrames[i]);
    }

    // Setting values
    currFrame = 0;
    emit changeCurrFrame(frames[currFrame]);
    emit changeFrameStructure(frames);
}

/**
 * @brief FrameManager::setSize
 * Changes the size of the frames
 * depending on what the user has
 * picked
 */
void FrameManager::setSize(int value)
{
    // Expanding or limiting the size of the frames
    for(int i = 0; i < frames.size(); i++)
    {
        QImage* newImage = new QImage(QSize(value, value), QImage::Format_ARGB32);
        QImage* oldImage = frames[i];
        for(int j = 0; j < value && j < oldImage->size().height(); j++)
        {
            for(int k = 0; k < value && k < oldImage->size().width(); k++)
            {
                newImage->setPixelColor(j, k, oldImage->pixelColor(j, k));
            }
        }

        // Clears garbage data
        if(value > oldImage->size().height())
        {
            for(int j = 0; j < value; j++)
            {
                for(int k = oldImage->size().height(); k < value; k++)
                {
                    newImage->setPixelColor(j, k, QColor(0, 0, 0, 0));
                }
            }

            for(int j = oldImage->size().height(); j < value; j++)
            {
                for(int k = 0; k < oldImage->size().height(); k++)
                {
                    newImage->setPixelColor(j, k, QColor(0, 0, 0, 0));
                }
            }

        }

        frames[i] = newImage;
        delete oldImage;
    }

    emit changeCurrFrame(frames[currFrame]);
    emit changeFrameStructure(frames);
}

/**
 * @brief FrameManager::addFrame
 * Add a new frame to the QVector
 * to work with
 */
void FrameManager::addFrame()
{
    // New QImage with transperant values
    QImage* newFrame = new QImage(frames[0]->size(), QImage::Format_ARGB32);
    QColor color(0, 0, 0, 0);
    newFrame->fill(color);
    frames.push_back(newFrame);
    currFrame = frames.size() - 1;

    // Signals
    emit changeCurrFrame(frames[currFrame]);
    emit changeFrameStructure(frames);
}

/**
 * @brief FrameManager::deleteFrame
 * Delete a frame from the QVector
 */
void FrameManager::deleteFrame()
{
    if(frames.size() == 1)
    {
        return;
    }

    frames.erase(frames.begin() + (int (currFrame)));
    if(currFrame != 0)
    {
        currFrame--;
    }

    // Signals
    emit changeCurrFrame(frames[currFrame]);
    emit changeFrameStructure(frames);
}

/**
 * @brief FrameManager::duplicateFrame
 * Creates a duplicate frame, of the
 * current frame that is selected
 */
void FrameManager::duplicateFrame()
{
    // Copying frame image over to new frame
    int size = frames[currFrame]->width();
    QImage *dupFrame = new QImage(QSize(size, size), QImage::Format_ARGB32);
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            QColor color = frames[currFrame]->pixelColor(i,j);
            dupFrame->setPixelColor(i, j, color);
        }
    }

    // Add the new frame to the vector
    frames.push_back(dupFrame);
    currFrame = frames.size() - 1;
    emit changeCurrFrame(frames[currFrame]);
    emit changeFrameStructure(frames);
}

/**
 * @brief FrameManager::moveLeft
 * Moves the current frame selection
 * to the left
 */
void FrameManager::moveLeft()
{
    if(currFrame == 0)
    {
        return;
    }

    currFrame--;
    emit changeCurrFrame(frames[currFrame]);
}

/**
 * @brief FrameManager::moveRight
 * Moves the current frame selection
 * to the right
 */
void FrameManager::moveRight()
{
    if(currFrame == frames.size() - 1)
    {
        return;
    }
    currFrame++;

    emit changeCurrFrame(frames[currFrame]);
}

/**
 * @brief FrameManager::update
 * Updates the QVector frames
 * whenenver they are being drawn
 */
void FrameManager::update()
{
    QImage blankImage(frames[0]->size(), QImage::Format_ARGB32);
    if(currFrame == 0 || currFrame == frames.size() - 1)
    {
        QColor newColor(0, 0, 0, 0);
        blankImage.fill(newColor);
    }

    // Currframe checks
    if(currFrame != 0)
    {
        ui->prevLabel->setPixmap(QPixmap::fromImage(*frames[currFrame - 1]));
        ui->prevLabelNum->setText(QString::number(currFrame));
    }
    else
    {
        ui->prevLabelNum->setText("");
        ui->prevLabel->setPixmap(QPixmap::fromImage(blankImage));
    }

    if(currFrame < frames.size() - 1)
    {
        ui->nextLabel->setPixmap(QPixmap::fromImage(*frames[currFrame + 1]));
        ui->nextLabelNum->setText(QString::number(currFrame + 2));
    }
    else
    {
        ui->nextLabelNum->setText("");
        ui->nextLabel->setPixmap(QPixmap::fromImage(blankImage));
    }

    ui->currLabel->setPixmap(QPixmap::fromImage(*frames[currFrame]));
    ui->currLabelNum->setText(QString::number(currFrame + 1));
    QTimer::singleShot(50, this, &FrameManager::update);
}
