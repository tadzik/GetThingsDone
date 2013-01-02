#include "Model.hpp"
#include "ProjectsView.hpp"
#include <QFile>

void Model::loadAll()
{
    SimpleActionsView *v;
    setSettings(Settings::getInstance());

    SimpleActionsModel *m;

    v = new SimpleActionsView(QString::fromUtf8("Next Actions"), view_);
    view_->addCategory(v);
    m = new SimpleActionsModel(v, v);
    addModel(m);

    v = new ProjectsView(QString::fromUtf8("Projects"), view_);
    view_->addCategory(v);
    m = new SimpleActionsModel(v, v);
    addModel(m);

    v = new ProjectsView(QString::fromUtf8("Someday/Maybe"), view_);
    view_->addCategory(v);
    m = new SimpleActionsModel(v, v);
    addModel(m);

    QFile file(filename_);

    if (!file.exists())
        return;

    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);

    settings_->loadContents(in);

    QList<SimpleActionsModel*>::iterator it;
    for (it = models_.begin(); it != models_.end(); it++) {
        (*it)->loadContents(in);
    }

    file.close();
}

void Model::saveAll()
{
    QFile file(filename_);

    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);

    settings_->saveContents(out);

    QList<SimpleActionsModel*>::iterator it;
    for (it = models_.begin(); it != models_.end(); it++) {
        (*it)->saveContents(out);
    }

    file.close();
}

void Model::addModel(SimpleActionsModel *m)
{
    models_.append(m);
    connect(m, SIGNAL(notifyChanged()), this, SLOT(modelChanged()));
}

void Model::setSettings(Settings *s)
{
    settings_ = s;
    connect(s, SIGNAL(notifyChanged()), this, SLOT(modelChanged()));
}

void Model::modelChanged()
{
    this->saveAll();
}
