/**
 * This controls everything for the DrawFrame.
 *
 * Author: Wasted Potential
 */

#include "drawscene.h"
#include <cmath>
#include <QTimer>

/**
 * Sets default values and constructs the DrawScene.
 */
DrawScene::DrawScene(QWidget* parent) :QGraphicsScene(parent)
{
    prevPoint.setX(0);
    prevPoint.setY(0);
    pencilSize = 0;
    color = Qt::black;
    mousePressed = false;
    setSceneRect(0, 0, 514, 514);
    grid = false;
    tool = pencil;
}

/**
 * Updates the DrawScene based on the saved image and whether or not the grid is on.
 */
void DrawScene::update()
{
    // Set the grid if it is toggled on.
    if (grid)
    {
        bool isGray = false;
        // Draw every square for the grid
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                addRect(((i * 512) / zoom) + 1, ((j * 512) / zoom) + 1,
                        512 / zoom, 512 / zoom, QPen(QColor(0,0,0,0)),
                        QBrush(isGray ? Qt::lightGray : Qt::white, Qt::BrushStyle::SolidPattern));
                isGray = !isGray;
            }
            isGray = !isGray;
        }
        // Draw all of the lines for the grid
        for (int i = 0; i < zoom + 1; i++)
        {
            addLine((i * 512) / zoom, 0, (i * 512) / zoom, 514, QPen(Qt::black));
            addLine(0, (i * 512) / zoom, 514, (i * 512) / zoom, QPen(Qt::black));
        }
    }
    // Sets everything to white when the grid is toggled off.
    else
    {
        addRect(0, 0, 515, 515, QPen(QColor(0,0,0,0)), QBrush(Qt::white, Qt::BrushStyle::SolidPattern));
    }
    // Add everything from the current image.
    for (int i = 0; i < zoom; i++)
    {
        for (int j = 0; j < zoom; j++)
        {
            int pixSize = 512 / zoom;
            if (grid)
            {
                pixSize -= 1;
            }
            addRect(((i * 512) / zoom) + 1, ((j * 512) / zoom) + 1,
                    pixSize, pixSize, QPen(QColor(0,0,0,0)),
                    QBrush(frame->pixelColor(i + tlx, j + tly), Qt::BrushStyle::SolidPattern));
        }
    }
}

/**
 * Handles when the mouse is pressed.
 */
void DrawScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    mousePressed = true;
    QPoint point = event->scenePos().toPoint();
    // Handles pencil and eraser
    if(tool == pencil || tool == eraser)
    {
        setSaved(false);
        addPoint(point, false);
    }
    // Handles bucket
    else if(tool == bucket)
    {
        setSaved(false);
        fill(point);
    }
    prevPoint = point;
}

/**
 * Handles when the mouse is released.
 */
void DrawScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    mousePressed = false;
}

/**
 * Handles when the mouse is moved.
 */
void DrawScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    // Handles pencil and eraser when the mouse is pressed
    if(mousePressed && (tool == pencil || tool == eraser))
    {
        // Calculate the line between the previous point and the current point.
        QPoint point = event->scenePos().toPoint();
        double xDiff = point.x() - prevPoint.x();
        double yDiff = point.y() - prevPoint.y();
        double scalar = sqrt((xDiff * xDiff) + (yDiff) * (yDiff));
        xDiff /= scalar;
        yDiff /= scalar;
        QPointF draw(prevPoint.x(), prevPoint.y());
        // Draw points along that line.
        for (int i = 0; i < scalar; i++)
        {
            draw.rx() += xDiff;
            draw.ry() += yDiff;
            addPoint(draw.toPoint(), false);
        }
        prevPoint = point;
    }
    // Handles pencil and eraser when the mouse is not pressed.
    else if(!mousePressed && (tool == pencil || tool == eraser))
    {
        // Restore the previous point and add the current point.
        QPoint point = event->scenePos().toPoint();
        addPoint(prevPoint, true);
        addPoint(point, false);
        prevPoint = point;
        prevCursor = QCursor::pos();
        // Remove the previous point in 100 ms.
        QTimer::singleShot(100, this, &DrawScene::timedRemove);
    }
    // Handles hand when the mouse is pressed.
    else if(mousePressed && tool == hand)
    {
        // Calculate the line between the current point and the previous point.
        QPoint point = event->scenePos().toPoint();
        tlx -= ((point.x() - prevPoint.x()) * zoom) / 512;
        tly -= ((point.y() - prevPoint.y()) * zoom) / 512;
        if(tlx < 0)
        {
            tlx = 0;
        }
        if(tly < 0)
        {
            tly = 0;
        }
        if(tlx + zoom > size)
        {
            tlx = size - zoom;
        }
        if(tly + zoom > size)
        {
            tly = size - zoom;
        }
        update();
        prevPoint = point;
    }
}

void DrawScene::timedRemove()
{
    if (prevCursor != QCursor::pos())
    {
        addPoint(prevPoint, true);
    }
}

void DrawScene::addPoint(QPoint point, bool restore)
{
    if (point.x() >= 0 && point.x() < 512 && point.y() >= 0 && point.y() < 512 && (tool == pencil || tool == eraser))
    {
        QPoint tlp(point.x(), point.y());
        int maxI, maxJ;
        int x = (point.x() * zoom) / 512;
        int y = (point.y() * zoom) / 512;
        int pixSize = 512 / zoom;
        if (grid)
        {
            pixSize -= 1;
        }
        switch(pencilSize)
        {
        case 0:
            maxI = maxJ = 1;
            break;
        case 1:
            if((point.x() % (512 / zoom)) < (256 / zoom))
            {
                x--;
            }
            if((point.y() % (512 / zoom)) < (256 / zoom))
            {
                y--;
            }
            maxI = maxJ = 2;
            if(x < 0)
            {
                x++;
                maxI = 1;
            }
            if(y < 0)
            {
                y++;
                maxJ = 1;
            }
            if(x >= zoom - 1)
            {
                maxI = 1;
            }
            if(y >= zoom - 1)
            {
                maxJ = 1;
            }
            break;
        case 2:
            x--;
            y--;
            maxI = maxJ = 3;
            if(x < 0)
            {
                x++;
                maxI = 2;
            }
            if(y < 0)
            {
                y++;
                maxJ = 2;
            }
            if(x >= zoom - 2)
            {
                maxI = 2;
            }
            if(y >= zoom - 2)
            {
                maxJ = 2;
            }
            break;
        case 3:
            x -= (point.x() % (512 / zoom)) < (256 / zoom) ? 2 : 1;
            y -= (point.y() % (512 / zoom)) < (256 / zoom) ? 2 : 1;
            maxI = maxJ = 4;
            if(x < 0)
            {
                x++;
                maxI = 3;
                if(x < 0)
                {
                    x++;
                    maxI = 2;
                }
            }
            if(y < 0)
            {
                y++;
                maxJ = 3;
                if(y < 0)
                {
                    y++;
                    maxJ = 2;
                }
            }
            if(x >= zoom - 3)
            {
                maxI = 3;
                if(x >= zoom - 2)
                {
                    maxI = 2;
                }
            }
            if(y >= zoom - 3)
            {
                maxJ = 3;
                if(y >= zoom - 2)
                {
                    maxJ = 2;
                }
            }
            break;
        default:
            return;
        }
        for(int i = 0; i < maxI; i++)
        {
            for(int j = 0; j < maxJ; j++)
            {
                if(grid && ((x + i) + (y + j)) % 2 == 1)
                {
                    addRect((((x + i) * 512) / zoom) + 1, (((y + j) * 512) / zoom) + 1, pixSize, pixSize,
                        QPen(QColor(0,0,0,0)), QBrush(Qt::lightGray, Qt::BrushStyle::SolidPattern));
                }
                else
                {
                    addRect((((x + i) * 512) / zoom) + 1, (((y + j) * 512) / zoom) + 1, pixSize, pixSize,
                        QPen(QColor(0,0,0,0)), QBrush(Qt::white, Qt::BrushStyle::SolidPattern));
                }
                if(tool == pencil)
                {
                    if(!restore)
                    {
                        if(mousePressed)
                        {
                            frame->setPixelColor(x + i + tlx, y + j + tly, color);
                        }
                        addRect((((x + i) * 512) / zoom) + 1, (((y + j) * 512) / zoom) + 1, pixSize, pixSize,
                            QPen(QColor(0,0,0,0)), QBrush(color, Qt::BrushStyle::SolidPattern));
                    }
                    else
                    {
                        addRect((((x + i) * 512) / zoom) + 1, (((y + j) * 512) / zoom) + 1, pixSize, pixSize,
                            QPen(QColor(0,0,0,0)), QBrush(frame->pixelColor(x + i + tlx, y + j + tly), Qt::BrushStyle::SolidPattern));
                    }
                }
                else if(tool == eraser)
                {
                    if(!restore)
                    {
                        if(mousePressed)
                        {
                            frame->setPixelColor(x + i + tlx, y + j + tly, QColor(0,0,0,0));
                        }
                    }
                    else
                    {
                        addRect((((x + i) * 512) / zoom) + 1, (((y + j) * 512) / zoom) + 1, pixSize, pixSize,
                            QPen(QColor(0,0,0,0)), QBrush(frame->pixelColor(x + i + tlx, y + j + tly), Qt::BrushStyle::SolidPattern));
                    }
                }
            }
        }
    }
}

/**
 * fills in a region with a certain color
 */
void DrawScene::fill(QPoint point)
{
    QPoint currPoint = QPoint(((point.x() * zoom) / 512) + tlx, ((point.y() * zoom) / 512) + tly);
    QColor currColor = frame->pixelColor(currPoint);
    if(currColor == color)
    {
        return;
    }
    fillHelper(currPoint, currColor);
    update();
}

/**
 * A recursive helper method to help the fill method
 */
void DrawScene::fillHelper(QPoint point, QColor currColor)
{
    frame->setPixelColor(point, color);
    QPoint leftPoint(point.x() - 1, point.y());
    QPoint upPoint(point.x(), point.y() - 1);
    QPoint rightPoint(point.x() + 1, point.y());
    QPoint downPoint(point.x(), point.y() + 1);
    if (leftPoint.x() >= 0 && frame->pixelColor(leftPoint) == currColor)
    {
        fillHelper(leftPoint, currColor);
    }
    if (upPoint.y() >= 0 && frame->pixelColor(upPoint) == currColor)
    {
        fillHelper(upPoint, currColor);
    }
    if (rightPoint.x() < size && frame->pixelColor(rightPoint) == currColor)
    {
        fillHelper(rightPoint, currColor);
    }
    if (downPoint.y() < size && frame->pixelColor(downPoint) == currColor)
    {
        fillHelper(downPoint, currColor);
    }
}

/**
 * Sets the current color
 */
void DrawScene::setColor(QColor c)
{
    color = c;
}

/**
 * sets the tool to the given tool
 */
void DrawScene::setTool(int toolNum)
{
    switch(toolNum)
    {
    case 0:
        tool = pencil;
        break;

    case 1:
        tool = hand;
        break;

    case 2:
        tool = eraser;
        break;

    case 3:
        tool = bucket;
        break;

    default:
        tool = undefined;
        break;
    }
}

/**
 * toggles the grid on and off
 */
void DrawScene::gridToggle()
{
    grid = !grid;
}

/**
 * Sets the drawScene to the currently selected frame
 */
void DrawScene::setFrame(QImage* frame)
{
    this->frame = frame;
    size = zoom = frame->size().width();
    tlx = tly = 0;
}

/**
 * sets the size of the pencil
 */
void DrawScene::setPencilSize(int size)
{
    pencilSize = size;
}

/**
 * Zooms in and out of the drawScene
 */
void DrawScene::zoomScene(bool zoomIn)
{
    if(zoomIn && zoom > 4)
    {
        zoom >>= 1;
        tlx += zoom >> 1;
        tly += zoom >> 1;
    }
    else if(!zoomIn && zoom < size)
    {
        tlx -= zoom >> 1;
        tly -= zoom >> 1;
        zoom <<= 1;
        if(tlx < 0)
        {
            tlx = 0;
        }
        if(tly < 0)
        {
            tly = 0;
        }
        if(tlx + zoom > size)
        {
            tlx = size - zoom;
        }
        if(tly + zoom > size)
        {
            tly = size - zoom;
        }
    }
}
