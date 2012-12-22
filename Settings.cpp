#include "Settings.hpp"

#include <QDebug>

Settings* Settings::getInstance()
{
    static Settings instance;

    return &instance;
}

QString& Settings::get(const QString& key)
{
    return map_[key];
}

void Settings::set(const QString& key, const QString& val)
{
    map_[key] = val;
    emit(notifyChanged());
}

void Settings::saveContents(QDataStream &out)
{
    out << map_;
}

void Settings::loadContents(QDataStream &in)
{
    in >> map_;
}
