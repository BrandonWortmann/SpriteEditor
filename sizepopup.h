/************************************************
 *      A8 - Sprite Editor                      *
 *  Author: Wasted Potential                    *
 *  CS 3505                                     *
 *                                              *
 *  header file for sizepopup                   *
 *                                              *
 ************************************************/

#ifndef SIZEPOPUP_H
#define SIZEPOPUP_H

#include <QWidget>


namespace Ui {
class SizePopup;
}

class SizePopup : public QWidget
{
    Q_OBJECT

public:
    explicit SizePopup(QWidget *parent = nullptr);
    ~SizePopup();
    Ui::SizePopup *ui;

};

#endif // SIZEPOPUP_H
