/************************************************
 *      A8 - Sprite Editor                      *
 *  Author: Wasted Potential                    *
 *  CS 3505                                     *
 *                                              *
 *  header file for helppopup                   *
 *                                              *
 ************************************************/

#ifndef HELPPOPUP_H
#define HELPPOPUP_H

#include <QWidget>

namespace Ui {
class HelpPopup;
}

class HelpPopup : public QWidget
{
    Q_OBJECT

public:
    explicit HelpPopup(QWidget *parent = nullptr);
    ~HelpPopup();

private:
    Ui::HelpPopup *ui;

};

#endif // HELPPOPUP_H
