/************************************************
 *      A8 - Sprite Editor                      *
 *  Author: Wasted Potential                    *
 *  CS 3505                                     *
 *                                              *
 *  main.cpp                                    *
 *  Underlying application that runs the        *
 *  mainwindow UI.                              *
 *                                              *
 ************************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>

/**
 * @brief main
 * Underlying application that
 * runs the MainWindow
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
