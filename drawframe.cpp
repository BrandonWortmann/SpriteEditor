/*
 * The DrawFramw class holds the draw scene, and allows the user to make and edit sprites
 * Author: Wasted Potential
*/


#include "drawframe.h"
#include "ui_drawframe.h"
#include <QFileDialog>

/*
 * The DrawFrame constructor takes in a Qwidget
*/
DrawFrame::DrawFrame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DrawFrame)
{
    ui->setupUi(this);
}

/*
 * we added our own method to act as a constructor to make it work with the other widgets
*/
void DrawFrame::setupFrame()
{
    drawScene = new DrawScene(this);
    ui->drawView->setScene(drawScene);
    ui->drawView->setCursor(Qt::CursorShape::CrossCursor);
}

/**
 * @brief DrawFrame::~DrawFrame
 * destructor for the DrawFrame
 */
DrawFrame::~DrawFrame()
{
    delete ui;
}

/**
 * @brief DrawFrame::setcolor
 * Sets the color for drawing
 * @param color
 */
void DrawFrame::setcolor(QColor color)
{
    drawScene->setColor(color);
}
/**
 * @brief DrawFrame::setPencilSize
 * sets the size of the pencil
 * @param size
 */
void DrawFrame::setPencilSize(int size)
{
    drawScene->setPencilSize(size);
}
/**
 * @brief DrawFrame::gridToggle
 * toggles the grid on and off
 */
void DrawFrame::gridToggle()
{
    drawScene->gridToggle();
    drawScene->update();
}
/**
 * @brief DrawFrame::setTool
 * sets which tool is being used
 * @param tool
 * the number associated with the tool
 * 0 = pencil
 * 1 = hand
 * 2 = eraser
 * 3 = bucket
 */
void DrawFrame::setTool(int tool)
{
    drawScene->setTool(tool);
    if(tool == 1)
    {
        ui->drawView->setCursor(Qt::CursorShape::OpenHandCursor);
    }
    else
    {
        ui->drawView->setCursor(Qt::CursorShape::CrossCursor);
    }
}

/**
 * @brief DrawFrame::zoom
 * zooms in and out
 * @param zoom
 * true means zoom in
 * false means zoom out
 */
void DrawFrame::zoom(bool zoom)
{
    drawScene->zoomScene(zoom);
    drawScene->update();
}
/**
 * @brief DrawFrame::setFrame
 * sets the drawframe to the current frame selected
 * @param frame
 * a pointer to the current frame
 */
void DrawFrame::setFrame(QImage* frame)
{
    drawScene->setFrame(frame);
    drawScene->update();
}
