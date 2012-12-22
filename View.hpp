#ifndef _VIEW_HPP_
#define _VIEW_HPP_

#include <QMainWindow>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QString>

#include "SimpleActionsView.hpp"
#include "SwipeDetector.hpp"

class View : public QMainWindow {
    Q_OBJECT;
public:
    View(QWidget *parent = NULL);
    SimpleActionsView* addCategory(const QString& name);
private:
    QVBoxLayout      *vbox_;
    QPushButton      *addNewButton_;
    QTabWidget       *tabbedView_;

    QAction     *settingsAction_;
    QAction     *helpAction_;
    QAction     *aboutAction_;

    void setupMenu();
private slots:
    void settingsDialog();
    void helpDialog();
    void aboutDialog();
    void addNewItemSlot();
    void swipeRightSlot();
    void swipeLeftSlot();
};

#endif
