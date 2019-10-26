#include "mainwindow.h"
#include "toolbar.h"
#include "ui_mainwindow.h"
#include "ui_toolbar.h"
#include <QDockWidget>
#include <QVBoxLayout>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ToolBar tool;
    toolBar = &tool;
    toolBar->ui->setupUi(ui->tbWidg);
}

MainWindow::~MainWindow()
{
    delete ui;
}

