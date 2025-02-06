#include <QCoreApplication>
#include <QSettings>

#include "te_settings/tesettings.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    TeSettings::setCommentSeparator(TeSettings::Hashtag);

    {
        TeSettings s1 ("./../TeSettings/test1.ini");
        s1.setValue("param1", "value1");
        s1.setComment("param1", "Это параметр 1");
        s1.setValue("param2", 1);
        s1.setComment("param2", "Это параметр 2");

        s1.setValue("SECTION_2/param2_1", "value2");
        s1.setValue("SECTION_2/param2_2", 2);
        s1.setComment("SECTION_2/", "Это секция 2\nА это тоже комментарий к секции 2");

        s1.beginGroup("SECTION_3");;
        s1.setComment("SECTION_3/", "Это секция 3");
        s1.setValue("param3_1", "value3");
        s1.setValue("param3_2", 3);
        s1.setComment("param3_2", "Это\nмногострочный\nкомментарий\nк параметру param3_2");
        s1.endGroup();

        s1.remove("GENERAL/param1");
        s1.remove("GENERAL/param2");

        qDebug().noquote() << s1;
        qDebug().noquote() << "childKeys в группе General:" << s1.childKeys();

        s1.beginGroup("SECTION_2");
        {
            qDebug().noquote() << "childKeys в группе SECTION_2:" << s1.childKeys();
        }
        s1.endGroup();
        qDebug().noquote() << "childGroups:" << s1.childGroups();
        qDebug().noquote() << "allKeys:" << s1.allKeys();
    } // Область видимости заканчивается, вызывается деструктор s1 и данные сохраняются в файл

    {
        TeSettings s2;

        s2.beginGroup("GROUP_1");
        {
            s2.setComment("", "Это группа 1");
            s2.setValue("param_1", "value_1");
            s2.setValue("param_2", 222);
        }
        s2.endGroup();
        s2.save("./../TeSettings/test2.ini");
        qDebug().noquote() << s2;
    } // Область видимости заканчивается, вызывается деструктор s2 и данные сохраняются в файл

    return 0;
}
