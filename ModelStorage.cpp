#include "ModelStorage.hpp"
#include <QFile>

void ModelStorage::loadAll()
{
    QFile file(filename_);

    if (!file.exists())
        return;

    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);

    QList<SimpleActionsModel*>::iterator it;
    for (it = models_.begin(); it != models_.end(); it++) {
        (*it)->loadContents(in);
    }

    file.close();
}

void ModelStorage::saveAll()
{
    QFile file(filename_);

    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);

    QList<SimpleActionsModel*>::iterator it;
    for (it = models_.begin(); it != models_.end(); it++) {
        (*it)->saveContents(out);
    }

    file.close();
}

void ModelStorage::addModel(SimpleActionsModel *m)
{
    models_.append(m);
    connect(m, SIGNAL(notifyChanged()), this, SLOT(modelChanged()));
}

void ModelStorage::modelChanged()
{
    this->saveAll();
}
