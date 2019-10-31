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

private:
    // data members
    QImage* frame;
    int tool, size, zoom, tlx, tly;
    bool grid;
    QColor color, prevColor;
    bool mousePressed;
    QPoint prevPoint;
    //methods
    void addPoint(QPoint point);


protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // DRAWSCENE_H
