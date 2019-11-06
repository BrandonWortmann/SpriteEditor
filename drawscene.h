/************************************************
 *      A8 - Sprite Editor                      *
 *  Author: Wasted Potential                    *
 *  CS 3505                                     *
 *                                              *
 *  header file for DrawScene                   *
 *                                              *
 ************************************************/

#ifndef DRAWSCENE_H
#define DRAWSCENE_H

#include <QGraphicsScene>
#include <QWidget>
#include <QGraphicsSceneMouseEvent>

class DrawScene : public QGraphicsScene
{
    Q_OBJECT

public:
    DrawScene(QWidget* parent);
    void update();
    void setTool(int tool);
    void setColor(QColor color);
    void gridToggle();
    void setFrame(QImage* frame);
    void setPencilSize(int size);
    void zoomScene(bool in);

signals:
    void setSaved(bool saved);

private:
    QImage* frame;
    int size, zoom, tlx, tly, pencilSize;
    bool grid;
    QColor color, prevColor;
    bool mousePressed;
    QPoint prevPoint;
    QPoint prevCursor;
    enum Tool{pencil, hand, eraser, bucket, undefined};
    Tool tool;
    void addPoint(QPoint point, bool restore);
    void fill(QPoint point);
    void fillHelper(QPoint point, QColor currColor);
    void timedRemove();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

};

#endif // DRAWSCENE_H
