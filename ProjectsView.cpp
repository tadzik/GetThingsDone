#include "ProjectsView.hpp"
#include "SimpleActionsModel.hpp"
#include "ProjectActions.hpp"
#include "AlarmHelper.hpp"
#include "Settings.hpp"
#include <QDebug>

#ifdef Q_WS_MAEMO_5
    #include <QMaemo5InformationBox>
#endif


void ProjectsView::itemSwiped(QModelIndex& idx)
{
    SimpleActionsModel *m = static_cast<SimpleActionsModel*>(this->model());
    QString name = m->data(idx, Qt::DisplayRole).toString();
    ProjectActions dialog(name, this);
    dialog.exec();

    if (dialog.result() == MARK_DONE) {
        return SimpleActionsView::itemSwiped(idx);
    }
    if (dialog.result() == POMODORO) {
        int timeout = Settings::getInstance()
                      ->get("pomodoro-time").toInt();
        AlarmHelper::setAlarm(timeout * 60);
#ifdef Q_WS_MAEMO_5
        QString note = QString("Alarm set for %1 minutes").arg(timeout);
        QMaemo5InformationBox::information(
            this, note,
            QMaemo5InformationBox::DefaultTimeout
        );
#endif
    }
}
