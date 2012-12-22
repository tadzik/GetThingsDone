#include "ProjectActions.hpp"

#include <QHBoxLayout>
#include <QPushButton>

ProjectActions::ProjectActions(QString& title, QWidget *p) : QDialog(p)
{
    setWindowTitle(title);

    QHBoxLayout *hbox = new QHBoxLayout(this);
    setLayout(hbox);

    QPushButton *done = new QPushButton("Mark as done");
    QPushButton *alrm = new QPushButton("Set a pomodoro alarm");

    connect(done, SIGNAL(clicked()), this, SLOT(doneClicked()));
    connect(alrm, SIGNAL(clicked()), this, SLOT(alrmClicked()));

    hbox->addWidget(done);
    hbox->addWidget(alrm);

    result_ = NOTHING;

    setAttribute(Qt::WA_DeleteOnClose);
}

void ProjectActions::doneClicked()
{
    result_ = MARK_DONE;
    accept();
}

void ProjectActions::alrmClicked()
{
    result_ = POMODORO;
    accept();
}
