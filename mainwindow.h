#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "toolbar.h"
#include "framemanager.h"
#include "drawframe.h"
#include "animationpreview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    ToolBar* toolBar;
    FrameManager* frameManager;
    DrawFrame* drawFrame;
    AnimationPreview* animationPreview;
};
#endif // MAINWINDOW_H
