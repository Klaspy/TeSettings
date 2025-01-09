#include <QCoreApplication>

#include "te_settings/tesettings.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    TeSettings s ("D:/Documents/TeSettings/build/Desktop_Qt_5_15_2_MinGW_64_bit-Debug/debug/test.ini");

    return 0;
}
