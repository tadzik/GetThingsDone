#include "SettingsDialog.hpp"

#include <QVBoxLayout>
#include <QCheckBox>

SettingsDialog::SettingsDialog(QObject *)
{
    settings_ = Settings::getInstance();

    QVBoxLayout *vbox = new QVBoxLayout(this);
    setLayout(vbox);

    QCheckBox *confirmDone = new QCheckBox("Confirm item removal", this);
    confirmDone->setCheckState(
        (settings_->get("confirm-removal") != "") ? Qt::Checked
                                                : Qt::Unchecked
    );
    connect(confirmDone, SIGNAL(stateChanged(int)),
            this, SLOT(confirmDoneSlot(int)));

    vbox->addWidget(confirmDone);

    setWindowTitle("GetThingsDone settings");
}

void SettingsDialog::confirmDoneSlot(int state)
{
    settings_->set("confirm-removal", state ? "1" : "");
}
