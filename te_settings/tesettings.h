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
    void beginGroup(const QString &group);
    void endGroup();

private:
    void readFile();
    void writeFile();
    void parseLine(QString &line, const int &lineNum);

private:
    QString group_;
    QMap<QString, QMap<QString, QString>> data_;

    QString filePath_;
};

#endif // TESETTINGS_H
