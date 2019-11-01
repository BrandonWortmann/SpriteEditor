#ifndef DRAWSCENE_H
#define DRAWSCENE_H

#include <QGraphicsScene>
#include <QWidget>
#include <QGraphicsSceneMouseEvent>

class DrawScene : public QGraphicsScene
{
public:
    DrawScene(QWidget* parent);

    void update();
    void setTool(int tool);
    void setColor(QColor color);
    void gridToggle();
    void setSize(int size);
    void setPencilSize(int size);
    void zoomScene(bool in);

private:
    // data members
    QImage* frame;
    int size, zoom, tlx, tly, pencilSize;
    bool grid;
    QColor color, prevColor;
    bool mousePressed;
    QPoint prevPoint;
    QPoint prevCursor;
    enum Tool{pencil, hand, eraser, bucket, undefined};
    Tool tool;
    //methods
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
