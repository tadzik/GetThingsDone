#ifndef _MODELSTORAGE_HPP_
#define _MODELSTORAGE_HPP_

#include "SimpleActionsModel.hpp"
#include <QList>
#include <QString>
#include <QDataStream>

class ModelStorage : public QObject {
    Q_OBJECT;
public:
    ModelStorage(QString& f) : filename_(f) {}
    void loadAll();
    void saveAll();
    void addModel(SimpleActionsModel *);

private:
    QString filename_;
    QList<SimpleActionsModel*> models_;
private slots:
    void modelChanged();
};

#endif
