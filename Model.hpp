#ifndef _MODELSTORAGE_HPP_
#define _MODELSTORAGE_HPP_

#include "SimpleActionsModel.hpp"
#include "Settings.hpp"
#include "View.hpp"
#include <QList>
#include <QString>
#include <QDataStream>

class Model : public QObject {
    Q_OBJECT;
public:
    Model(QString& f, View *w) : filename_(f), view_(w) {
        loadAll();
    }
    void loadAll();
    void saveAll();
    void addModel(SimpleActionsModel *);
    void setSettings(Settings *);
private:
    QString filename_;
    Settings *settings_;
    View     *view_;
    QList<SimpleActionsModel*> models_;
private slots:
    void modelChanged();
};

#endif
