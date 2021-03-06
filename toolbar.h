/************************************************
 *      A8 - Sprite Editor                      *
 *  Author: Wasted Potential                    *
 *  CS 3505                                     *
 *                                              *
 *  header file for toolbar                     *
 *                                              *
 ************************************************/

#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QWidget>
#include <QColorDialog>
#include "sizepopup.h"

namespace Ui {
class ToolBar;
}

class ToolBar : public QWidget
{
    Q_OBJECT

public:
    explicit ToolBar(QWidget *parent = nullptr);
    ~ToolBar();
    Ui::ToolBar *ui;
    QColor defaultColor;
    SizePopup *popUp;

   void closeSize();
   void setBtnColor(QColor);

public slots:
    void openSize();
    void colorSelected();
    void pencilSelected();
    void handSelected();
    void eraserSelected();
    void bucketSelected();
    void gridSelected();
    void zoomInSelected();
    void zoomOutSelected();
    void pencilSizeChanged(int value);

signals:
    void setColor(QColor);
    void setSize(int);
    void setTool(int);
    void setPencilSize(int);
    void toggleGrid();
    void toggleZoomIn();
    void toggleZoomOut();

};

#endif // TOOLBAR_H
