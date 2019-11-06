/************************************************
 *      A8 - Sprite Editor                      *
 *  Author: Wasted Potential                    *
 *  CS 3505                                     *
 *                                              *
 *  header file for mainwindow                  *
 *                                              *
 ************************************************/

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

public slots:
    void setColor(QColor);
    void setSize(int);
    void setTool(int);
    void setPencilSize(int);
    void toggleGrid();
    void toggleZoomIn();
    void toggleZoomOut();
    void changeCurrFrame(QImage*);
    void changeFrameStructure(QVector<QImage*>);
    void newSprite();
    void openSprite();
    void saveSprite();
    void saveAsSprite();
    void exportSprite();
    void closeSprite();
    void openHelpMenu();
    void setSaved(bool);


signals:
    void colorSelected();
    void sizeSelected();
    void newFrameSelected(QImage*);

private:
    Ui::MainWindow *ui;
    ToolBar* toolBar;
    FrameManager* frameManager;
    DrawFrame* drawFrame;
    AnimationPreview* animationPreview;
    uint size;
    bool isSaved;
    HelpPopup *help;
    QString fileName;
    QList<QVector<uint8_t>> pixelList;
    void closeEvent(QCloseEvent *event);

};
#endif // MAINWINDOW_H
