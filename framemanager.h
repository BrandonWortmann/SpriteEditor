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

    std::vector<QImage*> getFrames();
    void setFrames(std::vector<QImage*>);
    void setSize(int);
    void reloadFrame();

signals:
    void changeCurrFrame(QImage*);
    void changeFrameStructure(std::vector<QImage*>);


private:
    std::vector<QImage*> frames;
    int currFrame;

};

#endif // FRAMEMANAGER_H
