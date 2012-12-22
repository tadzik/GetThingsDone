#ifndef _PROJECTSVIEW_HPP_
#define _PROJECTSVIEW_HPP_

#include "SimpleActionsView.hpp"

class ProjectsView : public SimpleActionsView {
    Q_OBJECT;
public:
    ProjectsView(const QString& name, QWidget *p = NULL)
        : SimpleActionsView(name, p) {}

    void itemSwiped(QModelIndex&);
};

#endif
