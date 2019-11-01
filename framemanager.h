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
    void changeCurrFrames(QImage*, QImage*, QImage*);
    void changeFrameStructure(std::vector<QImage*>);

public slots:
    void addFrame();
    void deleteFrame();
    void moveLeft();
    void moveRight();

private:
    std::vector<QImage*> frames;
    size_t currFrame;

    void sendCurrFrames();

};

#endif // FRAMEMANAGER_H
