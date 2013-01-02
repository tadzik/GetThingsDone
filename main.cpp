#include "View.hpp"
#include "Model.hpp"
#include <QApplication>
#include <QString>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    View widok;

    QDir d;
    d.mkpath(QDir::homePath() + QString("/.config/GetThingsDone/"));
    QString filestore = QDir::homePath()
                      + QString("/.config/GetThingsDone/storage.dat");

    ModelStorage storage(filestore);

    Model model(&widok, &storage);

    widok.show();
    return app.exec();
}
