#ifndef _SIMPLEACTIONSVIEW_HPP_
#define _SIMPLEACTIONSVIEW_HPP_

#include <QTableView>
#include <QListView>
#include <QResizeEvent>
#include <QString>
#include "SwipeDetector.hpp"

class SimpleActionsView : public QListView {
    Q_OBJECT;
public:
    SimpleActionsView(const QString& name, QWidget *p = NULL);
    bool EventFilter(QObject *, QEvent *);
    void newItemDialog();
    const QString& name() { return name_; }
private slots:
    virtual void itemSwiped(QModelIndex&);
    void horizontalSwipeSlot(int, const QPoint&, const QPoint&);

signals:
    void swipeRight();
    void swipeLeft();

private:
    QString name_;
    SwipeDetector swipeDetector_; // handles mousePressEvent and mouseReleaseEvent
    void mousePressEvent(QMouseEvent *e) {
        swipeDetector_.mousePressEvent(e);
        QListView::mousePressEvent(e);
    }
    void mouseReleaseEvent(QMouseEvent *e) {
        swipeDetector_.mouseReleaseEvent(e);
        QListView::mousePressEvent(e);
    }

    void resizeEvent(QResizeEvent *);
};

#endif
