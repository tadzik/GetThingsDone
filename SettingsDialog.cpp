#include "SettingsDialog.hpp"

#include <QVBoxLayout>
#include <QStandardItemModel>
#include <QDebug>

SettingsDialog::SettingsDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("GetThingsDone settings");

    settings_ = Settings::getInstance();

    QVBoxLayout *vbox = new QVBoxLayout(this);
    setLayout(vbox);

    confirmDone_ = new QCheckBox("Confirm item removal", this);
    confirmDone_->setCheckState(
        (settings_->get("confirm-removal") != "") ? Qt::Checked
                                                : Qt::Unchecked
    );

    vbox->addWidget(confirmDone_);

#ifdef Q_WS_MAEMO_5
    selector_ = new QMaemo5ListPickSelector(this);
    QStandardItemModel *model = new QStandardItemModel(0, 1, selector_);
    for (int i = 5; i <= 120; i += 5) {
        QStandardItem *item = new QStandardItem(QString("%1").arg(i));
        item->setTextAlignment(Qt::AlignCenter);
        item->setEditable(false);
        model->appendRow(item);
    }
    selector_->setModel(model);
    int minutes = settings_->get("pomodoro-time").toInt();
    qDebug() << "pomodoro-time is" << minutes;
    selector_->setCurrentIndex((minutes / 5) - 1); // _should_ work...

    timeout_ = new QMaemo5ValueButton("Pomodoro timeout", this);
    timeout_->setValueLayout(QMaemo5ValueButton::ValueBesideText);
    timeout_->setPickSelector(selector_);

    vbox->addWidget(timeout_);

    setAttribute(Qt::WA_Maemo5AutoOrientation,      true);
    setAttribute(Qt::WA_Maemo5LandscapeOrientation, false);
    setAttribute(Qt::WA_Maemo5PortraitOrientation,  false);
#endif

    connect(this, SIGNAL(finished(int)), this, SLOT(finishedSlot()));
}

void SettingsDialog::finishedSlot()
{
#ifdef Q_WS_MAEMO_5
    int idx = static_cast<QMaemo5ListPickSelector*>(timeout_->pickSelector())->currentIndex();
    qDebug() << "selected index is" << idx;
    int minutes = (idx + 1) * 5;
    qDebug() << "setting pomodoro-time to " <<
        QString("%1").arg(minutes);
    settings_->set("pomodoro-time", QString("%1").arg(minutes));
#endif

    settings_->set("confirm-removal", confirmDone_->checkState() ? "1" : "");
}
