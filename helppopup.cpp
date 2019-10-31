#include "helppopup.h"
#include "ui_helppopup.h"

HelpPopup::HelpPopup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HelpPopup)
{
    ui->setupUi(this);
}

HelpPopup::~HelpPopup()
{
    delete ui;
}

//TO DO - WRITE HELPFUL DESCRIPTIONS
//TO DO - ADD IMAGES TO TOOLBAR BTN
//TO DO - add button for zoom in and zoom out
