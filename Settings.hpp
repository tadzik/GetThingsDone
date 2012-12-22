#ifndef _SETTINGS_HPP_
#define _SETTINGS_HPP_

#include <QMap>
#include <QString>
#include <QDataStream>
#include <QObject>

class Settings : public QObject {
    Q_OBJECT;
public:
    static Settings* getInstance();

    QString& get(const QString&);
    void set(const QString&, const QString&);
    void saveContents(QDataStream &);
    void loadContents(QDataStream &);
private:
    QMap<QString, QString> map_;
signals:
    void notifyChanged();
};

#endif
