#ifndef _SETTINGS_DIALOG_HPP_
#define _SETTINGS_DIALOG_HPP_

#include <QDialog>
#include "Settings.hpp"

class SettingsDialog : public QDialog {
    Q_OBJECT;
public:
    SettingsDialog(QWidget *p = NULL);
private:
    Settings *settings_;
private slots:
    void confirmDoneSlot(int);
};

#endif
