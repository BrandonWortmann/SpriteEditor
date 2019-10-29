#include "drawscene.h"
#include <cmath>

DrawScene::DrawScene(QWidget* parent) :QGraphicsScene(parent)
{
    size = 128;
    zoom = size;
    frame = new QImage(QSize(size, size), QImage::Format_ARGB32);
    color = Qt::green;
    mousePressed = false;
    setSceneRect(0, 0, 514, 514);
    grid = true;
    tlx = tly = 0;
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
    addPoint(point);
    mousePressed = true;
    prevPoint = point;
}

void DrawScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    mousePressed = false;
}

void DrawScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (mousePressed)
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
        frame->setPixelColor(((point.x() * zoom) / 512) + tlx, ((point.y() * zoom) / 512) + tly, color);
        int pixSize = (512 / zoom) - 1;
        if (grid)
        {
            pixSize -= 1;
        }
        addRect(point.x() - (point.x() % (512 / zoom)) + 1, point.y() - (point.y() % (512 / zoom)) + 1,
                pixSize, pixSize, QPen(color), QBrush(color, Qt::BrushStyle::SolidPattern));
    }
}
