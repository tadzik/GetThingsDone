#include "View.hpp"
#include <QFrame>
#include <QMenuBar>
#include <QMenu>
#include <QMessageBox>
#include <QDebug>

View::View(QWidget *parent) : QMainWindow(parent)
{
    QFrame *frame = new QFrame(this);

    vbox_         = new QVBoxLayout();
    addNewButton_ = new QPushButton("Add new item", this);
    tabbedView_   = new QTabWidget(this);

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

SimpleActionsView*
View::addCategory(const QString& name)
{
    SimpleActionsView *v = new SimpleActionsView(name, this);
    connect(v, SIGNAL(swipeRight()),   this, SLOT(swipeRightSlot()));
    connect(v, SIGNAL(swipeLeft()), this, SLOT(swipeLeftSlot()));
    tabbedView_->addTab(v, name);
    return v;
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

void View::settingsDialog() { this->NYI(); }
void View::helpDialog()     { this->NYI(); }
void View::aboutDialog()    { this->NYI(); }

void View::NYI()
{
    QMessageBox msg;
#ifdef Q_WS_MAEMO_5
    msg.setAttribute(Qt::WA_Maemo5AutoOrientation,      true);
    msg.setAttribute(Qt::WA_Maemo5LandscapeOrientation, false);
    msg.setAttribute(Qt::WA_Maemo5PortraitOrientation,  false);
#endif
    msg.setText("NYI");
    msg.exec();
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
