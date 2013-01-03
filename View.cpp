#include "View.hpp"
#include <QFrame>
#include <QMenuBar>
#include <QMenu>
#include <QMessageBox>
#include <QDebug>
#include "SettingsDialog.hpp"

View::View(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("GetThingsDone");

    QFrame *frame = new QFrame(this);

    vbox_         = new QVBoxLayout();
    addNewButton_ = new QPushButton("Add &new item", this);
    tabbedView_   = new QTabWidget(this);
    tabbedView_->setUsesScrollButtons(false);

    connect(addNewButton_, SIGNAL(clicked()), this, SLOT(addNewItemSlot()));

    vbox_->addWidget(addNewButton_);
    vbox_->addWidget(tabbedView_);
    
    frame->setLayout(vbox_);

    this->setCentralWidget(frame);

    this->setupMenu();

#ifdef Q_WS_MAEMO_5
    this->setAttribute(Qt::WA_Maemo5AutoOrientation,      true);
    this->setAttribute(Qt::WA_Maemo5LandscapeOrientation, false);
    this->setAttribute(Qt::WA_Maemo5PortraitOrientation,  false);
#endif
}

void
View::addCategory(SimpleActionsView *v)
{
    connect(v, SIGNAL(swipeRight()),   this, SLOT(swipeRightSlot()));
    connect(v, SIGNAL(swipeLeft()), this, SLOT(swipeLeftSlot()));
    tabbedView_->addTab(v, v->name());
}

void View::setupMenu()
{
    QMenuBar *menuBar = this->menuBar();

    settingsAction_ = new QAction("Settings", menuBar);
    helpAction_     = new QAction("Help", menuBar);
    aboutAction_    = new QAction("About", menuBar);

    menuBar->addAction(settingsAction_);
    menuBar->addAction(helpAction_);
    menuBar->addAction(aboutAction_);

    connect(settingsAction_, SIGNAL(triggered(bool)),
            this,         SLOT(settingsDialog()));
    connect(helpAction_,  SIGNAL(triggered(bool)),
            this,         SLOT(helpDialog()));
    connect(aboutAction_, SIGNAL(triggered(bool)),
            this,         SLOT(aboutDialog()));
}

void View::addNewItemSlot()
{
    QWidget *w = tabbedView_->currentWidget();
    if (w != NULL) {
        SimpleActionsView *v = static_cast<SimpleActionsView*>(w);
        v->newItemDialog();
    }
}

void View::settingsDialog() {
    SettingsDialog dialog(this);
    dialog.exec();
}

void View::helpDialog()
{
    QMessageBox::about(
        this, "Usage manual",
        "Use the 'Add new item' button to add a new entry in the current"
        " category. To remove an item, hold your finger on it and swipe "
        "right. You can look through categories by pressing their labels"
        " on top of the screen, or by swiping your finger horizontally "
        "in the free space below entries (if any).");
}

void View::aboutDialog()
{
    QMessageBox::about(
        this, "About GetThingsDone",
        "This program tries to help you organize your tasks, "
        "with an emphasis of not getting in your way too much, "
        "rather than making you waste more time on managing a "
        "ToDo list than on actually doing stuff.\n\n"
        "If you get an impression that I failed at the attempt, "
        "please contact me at tadeusz.sosnierz@onet.pl");
}

void View::swipeRightSlot()
{
    tabbedView_->setCurrentIndex(
        (tabbedView_->currentIndex() + 1) % tabbedView_->count()
    );
}
void View::swipeLeftSlot()
{
    int cur = tabbedView_->currentIndex() - 1;
    if (cur < 0) cur = tabbedView_->count() - 1;
    tabbedView_->setCurrentIndex(cur);
}
