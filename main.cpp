#include "loginscreen.h"
#include "qwidgettitle.h"

#include <QApplication>
#include"mainproject.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidgetTitle w;

    w.show();
    return a.exec();
}
