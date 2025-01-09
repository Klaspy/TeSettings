#ifndef TESETTINGS_H
#define TESETTINGS_H

#include <QObject>
#include <QDebug>
#include <QVariant>
#include <QString>
#include <QFile>
#include <QMap>

#define TE_SETTINGS_DEBUG

class TeSettings
{
public:
    TeSettings(const QString &filePath);

private:
    void readFile();
    void writeFile();

private:
    QString group_;
    QVariantMap data_;

    QString filePath_;
};

#endif // TESETTINGS_H
