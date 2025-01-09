#include "tesettings.h"

TeSettings::TeSettings(const QString &filePath)
    : filePath_ (filePath)
{
    readFile();
}

void TeSettings::beginGroup(const QString &group)
{
    group_ = group;
}

void TeSettings::endGroup()
{
    group_ = "GENERAL";
}

void TeSettings::readFile()
{
    // Чистим содержимое и сбрасываем текущую группу
    data_ = {};
    endGroup();

    if (!QFile::exists(filePath_))
    {
#ifdef TE_SETTINGS_DEBUG
        qWarning().noquote() << "Файл" << filePath_ << "не найден";
#endif
        return;
    }

    QFile ini (filePath_);
    if (!ini.open(QIODevice::ReadOnly))
    {
#ifdef TE_SETTINGS_DEBUG
        qWarning().noquote().nospace() << "Не удалось открыть файл " << filePath_ << ": " << ini.errorString();
#endif
        return;
    }

    int lineCnt = 0;
    while (true)
    {
        if (ini.atEnd())
        {
#ifdef TE_SETTINGS_DEBUG
            qWarning().noquote() << "Конец файла, строка" << lineCnt;
#endif
            break;
        }

        QString line (ini.readLine().simplified());
        parseLine(line, lineCnt);
        lineCnt++;
    }

    endGroup();

    qDebug().noquote() << data_;
}

void TeSettings::writeFile()
{

}

void TeSettings::parseLine(QString &line, const int &lineNum)
{
    // Пустая строка
    if (line.isEmpty())
    {
        return;
    }

    // Начало группы
    if (line.startsWith('['))
    {
        if (line.endsWith(']'))
        {
            group_ = line.mid(1, line.size() - 2);

            if (!data_.contains(group_))
            {
                data_.insert(group_, QMap<QString, QString> {});
            }
        }
        else
        {
#ifdef TE_SETTINGS_DEBUG
            qCritical().noquote() << "Не найден завершающий символ ']' в строке" << lineNum;
#endif
            return;
        }
    }
    else
    {
        const qsizetype equal_idx = line.indexOf('=');
        const qsizetype comment_idx = line.indexOf(';');

        if (equal_idx == -1)
        {
#ifdef TE_SETTINGS_DEBUG
            qCritical().noquote() << "Не найден символ '=' в строке" << lineNum;
#endif
            return;
        }

        // Вырезаем комментарии если они есть
        if (comment_idx != -1)
        {
            const QString comment (line.mid(comment_idx + 1));
            line.remove(comment_idx, line.length());
        }

        const QString key (line.mid(0, equal_idx));
        const QString value (line.mid(equal_idx + 1));
        data_[group_].insert(key, value);
    }
}
