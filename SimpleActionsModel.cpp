#include "SimpleActionsModel.hpp"

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

bool
SimpleActionsModel::setData(const QModelIndex& index,
                            const QVariant& val, int role)
{
    if (index.column() == 0) {
        if (index.row() <= this->entries_.count()) {
            this->entries_[index.row()] = val.toString();
            emit(notifyChanged());
            return true;
        }
    }

    return false;

    Q_UNUSED(role);
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
}

void SimpleActionsModel::saveContents(QDataStream &out)
{
    out << this->entries_;
}
