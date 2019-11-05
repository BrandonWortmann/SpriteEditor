#include "helppopup.h"
#include "ui_helppopup.h"

HelpPopup::HelpPopup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HelpPopup)
{
    ui->setupUi(this);
    ui->createText->setText("Welcome to \"Wasted Potential's\" Sprite editor! \n\nTo start creating your own sprite, "
        "select the pencil tool and click and hold anywhere on the draw panel to make changes. If you want to open"
        " an existing sprite, click on the file menu bar and select the open drop down menu option. Then choose a valid .ssp file."
        " \n\nAfter making changes, click on the file menu bar option and then choose save or saveAs. "
        "You can start start a new sprite from scratch by clicking the new file menu bar option. "
        "You can also click export and view your new sprite as an animated gif! Once you are done drawing, you may"
        " close the Sprite editor by pressing the close drop down menu.");

    ui->toolbarText->setText("The toolbar is the verticle bar on the left side of the editor, and consists of "
        "the following tools: tool size slider \nPencil \nHand \nEraser \nBucket \nGrid \nSize \nColor \nZoom in & Zoom out.\n"
        " In addition to choosing the pencil color, you can add your own custom colors by pressing the color toolbar option and"
        " then pressing the \"+\" under the custom text.");

    ui->animationPreviewText->setText("The animation preview is the top right window box that displays the "
         "frames that the frame manager holds in an animation. You can alter the playback speed by modifying the FPS slider value."
         " There is also an \"actual view\" button that will display the current sprite at it's actual size.");

    ui->frameManagerText->setText("The frame manager is the display bar at the bottom of the window. It allows users"
         " to control the current frame they want to edit as well as create new frames and delete unwanted frames. ");
}

HelpPopup::~HelpPopup()
{
    delete ui;
}

//TO DO - WRITE HELPFUL DESCRIPTIONS

