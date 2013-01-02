#ifndef _MODEL_HPP_
#define _MODEL_HPP_

#include <QString>
#include "ModelStorage.hpp"
#include "View.hpp"

class Model {
public:
    Model(View*, ModelStorage*);

private:
    QString      path_;
    View         *view_;
    ModelStorage *storage_;
};

#endif
