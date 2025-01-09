#include "tesettings.h"

TeSettings::TeSettings(const QString &filePath)
    : filePath_ (filePath)
{
    readFile();
}

void TeSettings::readFile()
{
    data_ = {};
    group_ = "GENERAL";

    if (!QFile::exists(filePath_))
    {
#ifdef TE_SETTINGS_DEBUG
        qWarning().noquote() << "File" << filePath_ << "not exist";
#endif
        return;
    }

    QFile ini (filePath_);
    if (!ini.open(QIODevice::ReadOnly))
    {
#ifdef TE_SETTINGS_DEBUG
        qWarning().noquote().nospace() << "Can't open " << filePath_ << ": " << ini.errorString();
#endif
        return;
    }

    int lineCnt = 0;
    while (true)
    {
        char data[1000];
        const qint64 res = ini.readLine(data, 1000);
        if (res <= 0)
        {
#ifdef TE_SETTINGS_DEBUG
            qWarning().noquote() << "End of file, line" << lineCnt;
#endif
            break;
        }

        QByteArray ba (data, res);
        ba.replace('\n', "");
        ba.replace('\r', "");

#ifdef TE_SETTINGS_DEBUG
        qDebug().noquote().nospace() << "Line " << lineCnt << ": " << ba;
#endif

        lineCnt++;
    }
}

void TeSettings::writeFile()
{

}
