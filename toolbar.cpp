/************************************************
 *      A8 - Sprite Editor                      *
 *  Author: Wasted Potential                    *
 *  CS 3505                                     *
 *                                              *
 *  toolbar.cpp                                 *
 *  UI for toolbar that manages button events.  *
 *  Handles the color and size popups.          *
 *                                              *
 ************************************************/

#include "toolbar.h"
#include "ui_toolbar.h"
#include "ui_sizepopup.h"
#include <QColor>
#include <QComboBox>
#include "sizepopup.h"
#include <QPalette>

/**
 * @brief ToolBar::ToolBar
 * This widget represents the toolbar. It holds the buttons for the tools and holds slots for
 * ui actions such as button pressed, and emits signals to mainwindow for changes to view. Also
 * holds the sizePopup widget and handles opening and closing that window.
 */
ToolBar::ToolBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ToolBar)
{
    // Build ui and sizePopup
    ui->setupUi(this);
    popUp = new SizePopup();

    // Connection between sizePopup's combobox result and size value
    connect(popUp->ui->comboBox, QOverload<int>::of(&QComboBox::activated),
            [=](int index)
    {
        QStringList sizeOptions = {"4","16","32","64", "128"};
        int size = sizeOptions[index].toInt();

        setSize(size);
        closeSize();
    });
}

/**
 * @brief ToolBar::~ToolBar
 * Remove toolBar and sizePopup from heap
 */
ToolBar::~ToolBar()
{
    delete ui;
    delete popUp;
}

/**
 * @brief ToolBar::colorSelected
 * Slot for the color wheel button being pressed. Will send two signals when color is selected.
 * One to set the color tool and one to change the button color.
 */
void ToolBar::colorSelected()
{
    QColorDialog colorWheel;
    QColor selectedColor = colorWheel.getColor(defaultColor, nullptr, "Select Color",QColorDialog::ShowAlphaChannel);

    setColor(selectedColor);
    defaultColor = selectedColor;
    setBtnColor(selectedColor);

}

/**
 * @brief ToolBar::openSize
 * Slot that catches the signal from toolbar size button being pressed
 * and displays the size popup.
 */
void ToolBar::openSize()
{
    popUp->show();
}

/**
 * @brief ToolBar::closeSize
 * Slot that catches the signal from sizePopup when a size is selected
 * from the comboBox, which closes the popup.
 */
void ToolBar::closeSize()
{
    popUp->close();
}

/**
 * @brief ToolBar::pencilSelected
 * Slot that catches the signal from toolbar pencil button being pressed
 * and sends a signal to the drawFrame, specifying to set the current tool to pencil
 */
void ToolBar::pencilSelected()
{
    setTool(0);
}

/**
 * @brief ToolBar::handSelected
 * Slot that catches the signal from toolbar hand button being pressed and
 * sends a signal to the drawFrame, specifying to set the current tool to hand
 */
void ToolBar::handSelected()
{
    setTool(1);

}

/**
 * @brief ToolBar::eraserSelected
 * Slot that catches the signal from toolbar eraser button being pressed and
 * sends a signal to the drawFrame, specifying to set the current tool to eraser
 */
void ToolBar::eraserSelected()
{
    setTool(2);

}

/**
 * @brief ToolBar::bucketSelected
 * Slot that catches the signal from toolbar bucket button being pressed and
 * sends a signal to the drawFrame, specifying to set the current tool to bucket
 */
void ToolBar::bucketSelected()
{
    setTool(3);

}
/**
 * @brief ToolBar::gridSelected
 * Slot that catches the signal from toolbar grid button being pressed and
 * sends a signal to the drawFrame, specifying to toggle the grid
 */
void ToolBar::gridSelected()
{
    toggleGrid();
}

/**
 * @brief ToolBar::zoomInSelected
 * Slot that catches the signal from toolbar zoom + button being pressed
 * and sends a signal to the drawFrame, specifying to zoom in
 */
void ToolBar::zoomInSelected()
{
    toggleZoomIn();
}

/**
 * @brief ToolBar::zoomOutSelected
 * Slot that catches the signal from toolbar zoom - button being pressed
 * and sends a signal to the drawFrame, specifying to zoom out
 */
void ToolBar::zoomOutSelected()
{
    toggleZoomOut();
}

/**
 * @brief ToolBar::pencilSizeChanged
 * Slot that catches the signal from pencil size slider value being changed
 * and sends a signal to the drawFrame, specifying the tool size
 */
void ToolBar::pencilSizeChanged(int size)
{
    setPencilSize(size);
}

/**
 * @brief ToolBar::setBtnColor
 * Slot that catches the signal from color button being pressed
 * and sends the signal (along with selected color) to the drawFrame
 * so it can change the pencil tool's color. Also changes button color.
 */
void ToolBar::setBtnColor(QColor selectedColor)
{
    QPalette pal = ui->colorBtn->palette();
    pal.setColor(QPalette::Button, QColor(selectedColor));
    ui->colorBtn->setAutoFillBackground(true);
    ui->colorBtn->setPalette(pal);
    ui->colorBtn->update();
}

