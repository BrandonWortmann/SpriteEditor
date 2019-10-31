#include "drawscene.h"
#include <cmath>

DrawScene::DrawScene(QWidget* parent) :QGraphicsScene(parent)
{
    size = 32;
    zoom = size;
    frame = new QImage(QSize(size, size), QImage::Format_ARGB32);
    color = Qt::black;
    mousePressed = false;
    setSceneRect(0, 0, 514, 514);
    grid = false;
    tlx = tly = 0;
    tool = pencil;
    update();
}

void DrawScene::update()
{
    if (grid)
    {
        bool isGray = false;
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                addRect(((i * 512) / zoom) + 1, ((j * 512) / zoom) + 1,
                        (512 / zoom) - 1, (512 / zoom) - 1, QPen(isGray ? Qt::lightGray : Qt::white),
                        QBrush(isGray ? Qt::lightGray : Qt::white, Qt::BrushStyle::SolidPattern));
                isGray = !isGray;
            }
            isGray = !isGray;
        }
        for (int i = 0; i < zoom + 1; i++)
        {
            addLine((i * 512) / zoom, 0, (i * 512) / zoom, 514, QPen(Qt::black));
            addLine(0, (i * 512) / zoom, 514, (i * 512) / zoom, QPen(Qt::black));
        }
    }
    else
    {
        addRect(0, 0, 515, 515, QPen(Qt::white), QBrush(Qt::white, Qt::BrushStyle::SolidPattern));
    }
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            int pixSize = (512 / zoom) - 1;
            if (grid)
            {
                pixSize -= 1;
            }
            addRect(((i * 512) / zoom) + 1, ((j * 512) / zoom) + 1,
                    pixSize, pixSize, QPen(frame->pixelColor(i, j)),
                    QBrush(frame->pixelColor(i, j), Qt::BrushStyle::SolidPattern));
        }
    }
}


void DrawScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QPoint point = event->scenePos().toPoint();
    if(tool == pencil || tool == eraser)
    {
        addPoint(point);
    }
    else if(tool == bucket)
    {
        fill(point);
    }
    mousePressed = true;
    prevPoint = point;
}

void DrawScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    mousePressed = false;
}

void DrawScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (mousePressed && (tool == pencil || tool == eraser))
    {
        QPoint point = event->scenePos().toPoint();
        double xDiff = point.x() - prevPoint.x();
        double yDiff = point.y() - prevPoint.y();
        double scalar = sqrt((xDiff * xDiff) + (yDiff) * (yDiff));
        xDiff /= scalar;
        yDiff /= scalar;
        QPointF draw(prevPoint.x(), prevPoint.y());
        for (int i = 0; i < scalar; i++)
        {
            draw.rx() += xDiff;
            draw.ry() += yDiff;
            addPoint(draw.toPoint());
        }
        prevPoint = point;
    }
}

void DrawScene::addPoint(QPoint point)
{
    if (point.x() >= 0 && point.x() < 512 && point.y() >= 0 && point.y() < 512)
    {
        int x = (point.x() * zoom) / 512;
        int y = (point.y() * zoom) / 512;
        int pixSize = (512 / zoom) - 1;
        if (grid)
        {
            pixSize -= 1;
        }
        if(tool == pencil)
        {
            frame->setPixelColor(x + tlx, y + tly, color);
            addRect(point.x() - (point.x() % (512 / zoom)) + 1, point.y() - (point.y() % (512 / zoom)) + 1,
                pixSize, pixSize, QPen(color), QBrush(color, Qt::BrushStyle::SolidPattern));
        }
        else if(tool == eraser)
        {
            frame->setPixelColor(x + tlx, y + tly, QColor(0,0,0,0));
            if(grid && (x + y) % 2 == 1)
            {
                addRect(point.x() - (point.x() % (512 / zoom)) + 1, point.y() - (point.y() % (512 / zoom)) + 1,
                    pixSize, pixSize, QPen(Qt::lightGray), QBrush(Qt::lightGray, Qt::BrushStyle::SolidPattern));
            }
            else
            {
                addRect(point.x() - (point.x() % (512 / zoom)) + 1, point.y() - (point.y() % (512 / zoom)) + 1,
                    pixSize, pixSize, QPen(Qt::white), QBrush(Qt::white, Qt::BrushStyle::SolidPattern));
            }
        }
    }
}

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

void DrawScene::setColor(QColor c)
{
    color = c;
}

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

void DrawScene::gridToggle()
{
    grid = !grid;
}

void DrawScene::setSize(int size)
{
    //TODO; Set size
}

void DrawScene::setPencilSize(int size)
{

}

void DrawScene::zoomScene(bool in)
{

}
