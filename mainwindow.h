#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "toolbar.h"
#include "framemanager.h"
#include "drawframe.h"
#include "animationpreview.h"
#include "sizepopup.h"
#include "helppopup.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    HelpPopup *help;

public slots:
    void setColor(QColor);
    void setSize(int);
    void setTool(int);
    void setPencilSize(int);
    void toggleGrid();
    void toggleZoomIn();
    void toggleZoomOut();
    void newSprite();
    void openSprite();
    void saveSprite();
    void saveAsSprite();
    void exportSprite();
    void closeSprite();
    void openHelpMenu();


signals:
    void colorSelected();
    void sizeSelected();

private:
    Ui::MainWindow *ui;
    ToolBar* toolBar;
    FrameManager* frameManager;
    DrawFrame* drawFrame;
    AnimationPreview* animationPreview;

};
#endif // MAINWINDOW_H
