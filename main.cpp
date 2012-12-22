#include "View.hpp"
#include "ModelStorage.hpp"
#include "Settings.hpp"
#include <QApplication>
#include <QString>
#include "ProjectsView.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    View widok;

    SimpleActionsView *v;
    QString filestore = QString::fromUtf8("storage.dat");

    ModelStorage storage(filestore);
    storage.setSettings(Settings::getInstance());

    SimpleActionsModel *m;

    v = new SimpleActionsView(QString::fromUtf8("Next Actions"), &widok);
    widok.addCategory(v);
    m = new SimpleActionsModel(v, v);
    storage.addModel(m);

    v = new ProjectsView(QString::fromUtf8("Projects"), &widok);
    widok.addCategory(v);
    m = new SimpleActionsModel(v, v);
    storage.addModel(m);

    storage.loadAll();

    widok.show();
    return app.exec();
}
