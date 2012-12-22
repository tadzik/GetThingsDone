#include "View.hpp"
#include "ModelStorage.hpp"
#include "Settings.hpp"
#include <QApplication>
#include <QString>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    View widok;

    SimpleActionsView *v;
    QString filestore = QString::fromUtf8("storage.dat");

    ModelStorage storage(filestore);
    storage.setSettings(Settings::getInstance());

    SimpleActionsModel *m;

    v = widok.addCategory(QString::fromUtf8("Next Actions"));
    m = new SimpleActionsModel(v);
    v->setModel(m);
    storage.addModel(m);

    v = widok.addCategory(QString::fromUtf8("Projects"));
    m = new SimpleActionsModel(v);
    v->setModel(m);
    storage.addModel(m);

    storage.loadAll();

    widok.show();
    return app.exec();
}
