#ifndef _MODELSTORAGE_HPP_
#define _MODELSTORAGE_HPP_

#include "SimpleActionsModel.hpp"
#include "Settings.hpp"
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
    void setSettings(Settings *);
private:
    QString filename_;
    Settings *settings_;
    QList<SimpleActionsModel*> models_;
private slots:
    void modelChanged();
};

#endif
