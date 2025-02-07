#ifndef TESETTINGS_H
#define TESETTINGS_H

#include <QObject>
#include <QDebug>
#include <QFile>
#include <QMap>

#ifdef Q_OS_WIN
#include "te_settingsGlobal.h"
#endif

// Этот дефайн включает дополнительный вывод для отладки возможных проблем парсинга
// #define TE_SETTINGS_DEBUG

// Этот дефайн дополняет класс до QObject'а, чтобы его можно было использовать из QML
// #define TE_SETTINGS_QOBJECT


class
#ifdef Q_OS_WIN
    TE_SETTINGS_EXPORT
#endif
    TeSettings
#ifdef TE_SETTINGS_QOBJECT
    : public QObject
#endif
{
#ifdef TE_SETTINGS_QOBJECT
    Q_OBJECT
#endif
public:

#ifdef TE_SETTINGS_QOBJECT
    // Открыть файл filePath. Если autosave == true, то данные сохранятся в файл при вызове деструктора
    TeSettings(const QString &filePath = "", const bool &autosave = true, QObject *parent = nullptr);
#else
    TeSettings(const QString &filePath = "", const bool &commentNewLine = false, const bool &autosave = true);
#endif
    ~TeSettings();

    static QString version();

// Основные интерфейсные методы
#ifdef TE_SETTINGS_QOBJECT
public slots:
#else
public:
#endif
    // Зайти в группу group конфигурационного файла
    void beginGroup(const QString &group);

    // Выйти из текущей группы конфигурационного файла
    void endGroup();

    // Получить значение параметра key (если не найден, возвращается defaultValue
    QVariant value(QString key, const QVariant &defaultValue = {}) const;
    // Получить строку комментария к параметру key
    QString comment(QString key) const;

    // Записать значение параметра key (если не найден, возвращается defaultValue
    void setValue(QString key, const QVariant &value);
    // Записать строку комментария к параметру key
    void setComment(QString key, const QString &comment);

    // Проверить наличие параметра key
    bool contains(QString key) const;

    // Удалить параметр key
    void remove(QString key);

    QString toString() const;

    // Принудительно вызвать процедуру сохранения в файл
    void save(const QString &filePath = "");

    // Получить список названий всех параметров в виде группа/параметр
    QStringList allKeys() const;

    // Получить список названий всех параметров в виде группа/параметр
    QStringList childKeys() const;

    // Получить список названий всех групп
    QStringList childGroups() const;

    void clear();

    friend QDebug operator<<(QDebug out, const TeSettings &settings);

    enum CommentSeparators {
        Semilicon = int(';'),
        Hashtag = int('#')
    };

    static char getCommentSeparator() {return commentSeparator;}
    static void setCommentSeparator(CommentSeparators separator);

private:
    void readFile();
    void writeFile();
    void parseLine(QString &line, const int &lineNum);

    QString extractGroupName(QString &key) const;

private:
    struct ParamData
    {
        QString value;
        QString comment;
    };

    struct GroupData
    {
        QMap<QString, ParamData> params;
        QString comment;
    };

private:
    QString group_;
    QString lastComment_;
    QMap<QString, GroupData> data_;

    QString filePath_;

    bool commentNewLine_;
    bool autosave_;

    static char commentSeparator;
};


#endif // TESETTINGS_H
