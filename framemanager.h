#ifndef FRAMEMANAGER_H
#define FRAMEMANAGER_H

#include <QWidget>

namespace Ui {
class FrameManager;
}

class FrameManager : public QWidget
{
    Q_OBJECT

public:
    explicit FrameManager(QWidget *parent = nullptr);
    ~FrameManager();

private:
    Ui::FrameManager *ui;
};

#endif // FRAMEMANAGER_H
