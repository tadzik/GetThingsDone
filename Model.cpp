#include "Model.hpp"
#include "Settings.hpp"
#include "ProjectsView.hpp"

Model::Model(View *view, ModelStorage *storage) : view_(view),
                                                  storage_(storage)
{
    SimpleActionsView *v;
    storage->setSettings(Settings::getInstance());

    SimpleActionsModel *m;

    v = new SimpleActionsView(QString::fromUtf8("Next Actions"), view_);
    view_->addCategory(v);
    m = new SimpleActionsModel(v, v);
    storage->addModel(m);

    v = new ProjectsView(QString::fromUtf8("Projects"), view_);
    view_->addCategory(v);
    m = new SimpleActionsModel(v, v);
    storage->addModel(m);

    storage->loadAll();
}
