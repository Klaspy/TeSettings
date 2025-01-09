#include <QCoreApplication>

#include "te_settings/tesettings.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    TeSettings s ("D:/Documents/TeSettings/test.ini");

    return 0;
}
