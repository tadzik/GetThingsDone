#ifndef _NEXTACTIONSMODEL_HPP_
#define _NEXTACTIONSMODEL_HPP_

#include <QAbstractTableModel>
#include <QAbstractItemView>
#include <QList>
#include <QString>
#include <QDataStream>
#include "SimpleActionsView.hpp"

class SimpleActionsModel : public QAbstractTableModel {
    Q_OBJECT;
public:
    SimpleActionsModel(SimpleActionsView *v, QObject *parent = NULL)
        : QAbstractTableModel(parent)
    {
        v->setModel(this);
    }

    int rowCount(const QModelIndex&) const;
    int columnCount(const QModelIndex&) const;
    QVariant data(const QModelIndex&, int r = Qt::DisplayRole) const;
    void markElementDone(QModelIndex&);
    void addNewElement(QString&);
    bool removeRows(int, int, const QModelIndex& p = QModelIndex());
    bool insertRow(int row, const QModelIndex& p = QModelIndex());

    void saveContents(QDataStream&);
    void loadContents(QDataStream&);
private:
    QList<QString> entries_;

signals:
    void notifyChanged();
};

#endif
