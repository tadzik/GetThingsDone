#include "SimpleActionsView.hpp"
#include "SimpleActionsModel.hpp"
#include "Settings.hpp"
#include <QModelIndex>
#include <QMouseEvent>
#include <QInputDialog>
#include <QMessageBox>

#include <QDebug>

SimpleActionsView::SimpleActionsView(const QString& name, QWidget *parent) : QListView(parent)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    swipeDetector_.setThreshold(qMin(this->width(), this->height()) / 5);
    connect(&swipeDetector_,
            SIGNAL(horizontalSwipe(int, const QPoint&, const QPoint&)),
            this, SLOT(horizontalSwipeSlot(int, const QPoint&, const QPoint&)));

    Q_UNUSED(name);
}

void SimpleActionsView::resizeEvent(QResizeEvent *)
{
    swipeDetector_.setThreshold(qMin(this->width(), this->height()) / 5);
}

void SimpleActionsView::markDone(QModelIndex& idx)
{
    SimpleActionsModel *m = static_cast<SimpleActionsModel*>(this->model());

    if (Settings::getInstance()->get("confirm-removal") != "") {
        QString item = m->data(idx, Qt::DisplayRole).toString();
        QString question = QString("Are you sure you want to remove %1?")
            .arg(item);

        QMessageBox::StandardButton result;

        result = QMessageBox::question(
            this, "Confirm item removal", question,
            QMessageBox::Yes | QMessageBox::No
        );

        if (result != QMessageBox::Yes)
            return;
    }

    m->markElementDone(idx);
}

void
SimpleActionsView::newItemDialog()
{
    bool ok;
    QString text = QInputDialog::getText(
        this, "Add new item", "Description:", QLineEdit::Normal, "", &ok
    );
    if (ok && !text.isEmpty()) {
        SimpleActionsModel *m = static_cast<SimpleActionsModel*>(this->model());
        m->addNewElement(text);
    }
}

void
SimpleActionsView::horizontalSwipeSlot(int direction,
                                     const QPoint& from,
                                     const QPoint& to)
{
    if (direction == 1) {
        qDebug () << "swipe right on qlistview";
        QModelIndex from_idx = this->indexAt(mapFromGlobal(from));
        if (from_idx.isValid()) {
            QModelIndex to_idx   = this->indexAt(mapFromGlobal(to));
            if (from_idx == to_idx) {
                qDebug () << "swipe right on the same element, removing"
                    << to_idx.row();
                this->markDone(to_idx);
            }
        } else {
            emit(swipeRight());
        }
    } else {
        emit(swipeLeft());
    }
    
}
