#ifndef FRAMEMANAGER_H
#define FRAMEMANAGER_H

#include <QWidget>
#include <QImage>

namespace Ui {
class FrameManager;
}

class FrameManager : public QWidget
{
    Q_OBJECT

public:
    explicit FrameManager(QWidget *parent = nullptr);
    ~FrameManager();
    Ui::FrameManager *ui;

    void setupFrameManager();
    QVector<QImage*> getFrames();
    void setFrames(QVector<QImage*>);
    void setSize(int);
    void reloadFrame();

signals:
    void changeCurrFrame(QImage*);
    void changeFrameStructure(QVector<QImage*>);

public slots:
    void addFrame();
    void deleteFrame();
    void moveLeft();
    void moveRight();

private:
    QVector<QImage*> frames;
    int currFrame;

    void update();
};

#endif // FRAMEMANAGER_H
