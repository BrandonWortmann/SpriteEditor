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
    QColorDialog colorWheel;
    SizePopup *p;

   void closeSize();

public slots:
    void openSize();
    void colorSelected();
    void pencilSelected();
    void handSelected();
    void eraserSelected();
    void bucketSelected();
    void gridSelected();
    void zoomSelected();

signals:
    void setColor(QColor);
    void setSize(int);
    void setTool(int);
    void toggleGrid();
    void toggleZoom();

};

#endif // TOOLBAR_H
