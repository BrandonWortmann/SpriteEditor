#include "toolbar.h"
#include "ui_toolbar.h"
#include "ui_sizepopup.h"
#include <QColor>
#include <iostream>
#include <QPushButton>
#include <QComboBox>
#include "sizepopup.h"
#include <QPalette>
ToolBar::ToolBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ToolBar)
{
    ui->setupUi(this);

    p = new SizePopup();
    connect(p->ui->comboBox, QOverload<int>::of(&QComboBox::activated),
            [=](int index)
    {
        QStringList sizeOptions = {"4","16","32","64", "128"};

        int size = sizeOptions[index].toInt();

        setSize(size);
        closeSize();
    });

    defaultColor.setRgb(255,255,255,0);
}

ToolBar::~ToolBar()
{
    delete ui;
    delete p;
}



void ToolBar::colorSelected(){
    QColorDialog colorWheel(defaultColor, nullptr);
    QColor selectedColor = colorWheel.getColor();
    setColor(selectedColor);
    defaultColor = selectedColor;

    QPalette pal = ui->colorBtn->palette();
    pal.setColor(QPalette::Button, QColor(selectedColor));
    ui->colorBtn->setAutoFillBackground(true);
    ui->colorBtn->setPalette(pal);
    ui->colorBtn->update();
}

void ToolBar::openSize()
{
    p->show();
}


void ToolBar::closeSize()
{
    p->close();
}

void ToolBar::pencilSelected()
{
    setTool(0);
}

void ToolBar::handSelected()
{
    setTool(1);

}

void ToolBar::eraserSelected()
{
    setTool(2);

}

void ToolBar::bucketSelected()
{
    setTool(3);

}

void ToolBar::gridSelected()
{
    toggleGrid();
}

void ToolBar::zoomInSelected()
{
    toggleZoomIn();
}

void ToolBar::zoomOutSelected()
{
    toggleZoomOut();
}

void ToolBar::pencilSizeChanged(int size)
{
    setPencilSize(size);
}

