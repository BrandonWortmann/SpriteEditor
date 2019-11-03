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
