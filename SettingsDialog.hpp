#ifndef _SETTINGS_DIALOG_HPP_
#define _SETTINGS_DIALOG_HPP_

#include <QDialog>
#include <QCheckBox>
#include "Settings.hpp"

#ifdef Q_WS_MAEMO_5
    #include <QMaemo5ValueButton>
    #include <QMaemo5ListPickSelector>
#endif

class SettingsDialog : public QDialog {
    Q_OBJECT;
public:
    SettingsDialog(QWidget *p = NULL);
private:
    Settings *settings_;
    QCheckBox *confirmDone_;
#ifdef Q_WS_MAEMO_5
    QMaemo5ValueButton *timeout_;
    QMaemo5ListPickSelector *selector_;
#endif
private slots:
    void finishedSlot();
};

#endif
