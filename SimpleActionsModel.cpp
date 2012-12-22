#include "SimpleActionsModel.hpp"

#include <QDebug>

int
SimpleActionsModel::rowCount(const QModelIndex&)
const
{
    return this->entries_.count();
}

int
SimpleActionsModel::columnCount(const QModelIndex&)
const
{
    return 1;
}

QVariant
SimpleActionsModel::data(const QModelIndex &index, int role) const
{
    if (index.column() == 0) {
        if (role == Qt::DisplayRole) {
            if (index.row() <= this->entries_.count())
                return this->entries_[index.row()];
        }
    }

    return QVariant();
}

bool
SimpleActionsModel::removeRows(int row, int c, const QModelIndex& parent)
{
    this->beginRemoveRows(parent, row, row + 1);
    this->entries_.removeAt(row);
    emit(notifyChanged());
    this->endRemoveRows();

    return true;

    Q_UNUSED(c);
}

void
SimpleActionsModel::markElementDone(QModelIndex& i)
{
    this->removeRows(i.row(), 1);
}

void
SimpleActionsModel::addNewElement(QString& t)
{
    this->beginInsertRows(QModelIndex(), 0, 0);
    this->entries_.prepend(t);
    emit(notifyChanged());
    this->endInsertRows();
}

void SimpleActionsModel::loadContents(QDataStream& in)
{
    in >> this->entries_;

    qDebug() << this->entries_.count() << "elements";

    for (int i = 0; i < this->entries_.count(); i++) {
        qDebug() << "Element " << i << ":" << this->entries_[i];
    }
}

void SimpleActionsModel::saveContents(QDataStream &out)
{
    out << this->entries_;
}
