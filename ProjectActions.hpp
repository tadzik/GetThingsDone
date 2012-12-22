#ifndef _PROJECTACTIONS_HPP_
#define _PROJECTACTIONS_HPP_

#include <QString>
#include <QDialog>

enum ProjectActionsResult { NOTHING, MARK_DONE, POMODORO };

class ProjectActions : public QDialog {
    Q_OBJECT;
public:
    ProjectActions(QString&, QWidget *p = NULL);
    ProjectActionsResult result() { return result_; }
private:
    ProjectActionsResult result_;
private slots:
    void doneClicked();
    void alrmClicked();
};

#endif
