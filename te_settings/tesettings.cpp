#include "tesettings.h"

// Открыть файл filePath. Если autosave == true, то данные сохранятся в файл при вызове деструктора
#ifdef TE_SETTINGS_QOBJECT
TeSettings::TeSettings(const QString &filePath, const bool &autosave, QObject *parent)
    : QObject   (parent)
    , filePath_ (filePath)
    , autosave_ (autosave)
#else
TeSettings::TeSettings(const QString &filePath, const bool &autosave)
    : filePath_ (filePath)
    , autosave_ (autosave)
#endif
{
if (!filePath_.isEmpty())
{
    readFile();
}
}

TeSettings::~TeSettings()
{
    if (autosave_)
    {
        save();
    }
}

void TeSettings::beginGroup(const QString &group)
{
    group_ = group;
}

void TeSettings::endGroup()
{
    group_ = "General";
}

QString TeSettings::extractGroupName(QString &key) const
{
    // Если есть '/', значит название группы включено в ключ. Надо разбить
    const qsizetype index = key.indexOf('/');

    if (index == -1)
    {
        return group_;
    }
    else
    {
        const QString tmp (key.mid(0, index));
        key = key.mid(index + 1);
        return tmp;
    }
}

QVariant TeSettings::value(QString key, const QVariant &defaultValue) const
{
    // Если есть '/', значит название группы включено в ключ. Надо разбить
    const QString group (extractGroupName(key));

    if (data_.contains(group))
    {
        const auto &params (data_[group].params);
        if (params.contains(key))
        {
            return params[key].value;
        }
    }

    return defaultValue;
}

QString TeSettings::comment(QString key) const
{
    // Если есть '/', значит название группы включено в ключ. Надо разбить
    const QString group (extractGroupName(key));

    if (data_.contains(group))
    {
        // Если названия параметра нет, то надо вернуть коммент группы
        if (key.isEmpty())
        {
            return data_[group].comment;
        }

        const auto &params (data_[group].params);
        if (params.contains(key))
        {
            return params[key].comment;
        }
    }

    return "";
}

void TeSettings::setValue(QString key, const QVariant &value)
{
    // Если есть '/', значит название группы включено в ключ. Надо разбить
    const QString group (extractGroupName(key));

    if (!data_.contains(group))
    {
        data_.insert(group, {});
    }

    auto &params (data_[group].params);
    params.insert(key, ParamData {.value = value.toString(), .comment = ""});
}

void TeSettings::setComment(QString key, const QString &comment)
{
    // Если есть '/', значит название группы включено в ключ. Надо разбить
    const QString group (extractGroupName(key));

    if (!data_.contains(group))
    {
        data_.insert(group, {});
    }

    auto &params (data_[group].params);
    if (params.contains(key))
    {
        params[key].comment = comment;
    }

    if (key.isEmpty())
    {
        data_[group].comment = comment;
    }

    return;
}

bool TeSettings::contains(QString key) const
{
    // Если есть '/', значит название группы включено в ключ. Надо разбить
    const QString group (extractGroupName(key));

    return data_.contains(group) && data_[group].params.contains(key);
}

void TeSettings::remove(QString key)
{
    const QString group (extractGroupName(key));

    if (data_.contains(group))
    {
        data_[group].params.remove(key);

        if (data_[group].params.count() == 0)
        {
            data_.remove(group);
        }
    }
}

void TeSettings::readFile()
{
    // Чистим содержимое и сбрасываем текущую группу
    data_ = {};
    lastComment_.clear();
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
            ini.close();
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
    lastComment_.clear();
}

void TeSettings::writeFile()
{
    QFile ini (filePath_);
    if (!ini.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
#ifdef TE_SETTINGS_DEBUG
        qWarning().noquote().nospace() << "Не удалось открыть файл " << filePath_ << ": " << ini.errorString();
#endif
        return;
    }

    ini.write(this->toString().toUtf8());
    ini.close();
}

void TeSettings::parseLine(QString &line, const int &lineNum)
{
#ifdef TE_SETTINGS_DEBUG
    qDebug().noquote().nospace() << "Строка " << lineNum << ": \"" << line << "\"";
#else
    Q_UNUSED(lineNum)
#endif

    // Пустая строка
    if (line.isEmpty())
    {
        return;
    }

    // Комментарий
    if (line.startsWith(';'))
    {
#ifdef TE_SETTINGS_DEBUG
        qDebug().noquote() << "Найден комментарий";
#endif
        if (!lastComment_.isEmpty())
        {
            lastComment_.append('\n');
        }
        lastComment_.append(line.mid(1).simplified());
    }
    // Начало группы
    else if (line.startsWith('['))
    {
        const qsizetype end_idx (line.indexOf(']'));
        const qsizetype comment_idx (line.indexOf(';'));

        if (end_idx == -1)
        {
#ifdef TE_SETTINGS_DEBUG
            qCritical().noquote() << "Не найден завершающий символ ']' в строке" << lineNum;
#endif
            return;
        }

#ifdef TE_SETTINGS_DEBUG
        qDebug().noquote() << "Найдено начало группы";
#endif

        // Название группы без '[' и ']'
        group_ = line.mid(1, end_idx - 1);

        // Вырезаем комментарии если они есть
        if (comment_idx != -1)
        {
            const QString comment (line.mid(comment_idx + 1).simplified());
            line.remove(comment_idx, line.length());

#ifdef TE_SETTINGS_DEBUG
            qDebug().noquote().nospace() << "Найден комментарий \"" << comment << "\"";
#endif

            // Если после параметра есть комментарий
            if (!comment.isEmpty())
            {
                // Если перед текущим параметром не было комментария, то используем только комментарий из конца строки
                if (lastComment_.isEmpty())
                {
                    lastComment_ = comment;
                }
                else // Если был, то объединяем его с комментарием из конца строки
                {
                    lastComment_.append('\n');
                    lastComment_.append(comment);
                }
            }
        }

        // Если ещё нет такой группы
        if (!data_.contains(group_))
        {
            data_.insert(group_, GroupData {.params = {}, .comment = lastComment_});
            lastComment_.clear();
        }
    }
    // Параметр
    else if (line.contains('='))
    {
#ifdef TE_SETTINGS_DEBUG
        qDebug().noquote() << "Найден параметр";
#endif
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
            const QString comment (line.mid(comment_idx + 1).simplified());
            line.remove(comment_idx, line.length());

#ifdef TE_SETTINGS_DEBUG
            qDebug().noquote().nospace() << "Найден комментарий \"" << comment << "\"";
#endif

            // Если после параметра есть комментарий
            if (!comment.isEmpty())
            {
                // Если перед текущим параметром не было комментария, то используем только комментарий из конца строки
                if (lastComment_.isEmpty())
                {
                    lastComment_ = comment;
                }
                else // Если был, то объединяем его с комментарием из конца строки
                {
                    lastComment_.append('\n');
                    lastComment_.append(comment);
                }
            }
        }

        const QString key (line.mid(0, equal_idx).trimmed());
        const QString value (line.mid(equal_idx + 1).trimmed());
        data_[group_].params.insert(key, ParamData {.value = value, .comment = lastComment_});
        lastComment_.clear();
    }
}

QString TeSettings::toString() const
{
    QString result;

    for (const auto &groupName : data_.keys())
    {
        const GroupData &group (data_[groupName]);

        if (group.params.count() == 0)
        {
            continue;
        }

        if (!group.comment.isEmpty())
        {
            for (const auto &line : group.comment.split('\n'))
            {
                result.append("; ");
                result.append(line);
                result.append('\n');
            }
        }

        result.append('[');
        result.append(groupName);
        result.append(']');

        QList<QString> params (group.params.keys());

        // Соритурем хитро: если можем обе строки можем привести к числу, то сортируем как числа. Иначе - как строки
        const auto compare = [](const QString &a, const QString &b)
        {
            bool res = false;
            const qint64 aa = a.toLongLong(&res);
            if (res)
            {
                const qint64 bb = b.toLongLong(&res);
                if (res)
                {
                    return aa < bb;
                }
            }
            return a < b;
        };
        std::sort(params.begin(), params.end(), compare);

        for (const auto &paramName : params)
        {
            const ParamData &param (group.params[paramName]);
            result.append('\n');

            const QStringList commentLines (param.comment.split('\n'));

            if (commentLines.length() > 1)
            {
                for (const auto &line : commentLines)
                {
                    result.append("; ");
                    result.append(line);
                    result.append('\n');
                }
            }

            result.append(paramName);
            result.append('=');
            result.append(param.value);

            if (commentLines.length() == 1 && !commentLines.first().isEmpty())
            {
                result.append("\t; ");
                result.append(commentLines.first());
            }

        }
        result.append('\n');
        result.append('\n');
    }

    result.remove(result.length() - 2, 1);

    return result;
}

void TeSettings::save(const QString &filePath)
{
    if (filePath_.isEmpty())
    {
        filePath_ = filePath;
    }

    if (!filePath_.isEmpty())
    {
        writeFile();
    }
}

QStringList TeSettings::allKeys() const
{
    QStringList res;
    const auto groups (data_.keys());

    for (const auto &group : groups)
    {
        const auto params (data_[group].params.keys());

        if (group == "General")
        {
            for (const auto &param : params)
            {
                res.append(param);
            }
        }
        else
        {
            for (const auto &param : params)
            {
                res.append(group + "/" + param);
            }
        }
    }

    return res;
}

QStringList TeSettings::childKeys() const
{
    if (data_.contains(group_))
    {
        return data_[group_].params.keys();
    }

    return {};
}

QStringList TeSettings::childGroups() const
{
    return data_.keys();
}

void TeSettings::clear()
{
    data_.clear();
}

QString TeSettings::version()
{
#ifdef TE_SETTINGS_QOBJECT
    return QString (APP_VERSION) + "-qml";
#else
    return APP_VERSION;
#endif
}

QDebug operator<<(QDebug out, const TeSettings &settings)
{
    return (out << settings.toString());
}

