#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);//QApplication системный класс надстройка над main
    QTranslator myappTraslator;
    myappTraslator.load(QApplication::applicationDirPath()+
                        QDir::separator()+"lang_ru.qm");
    a.installTranslator(&myappTraslator);
    Widget w;
    w.show();
    return a.exec();//обычно 0 возвращается если все выполняется
}
