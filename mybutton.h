#ifndef MYBUTTON_H
#define MYBUTTON_H
#include <QPushButton>
#include <QtWebKitWidgets>
#include <QTimer>

class MyButton: public QPushButton
{
    Q_OBJECT
public:
    MyButton(QString text, QWidget *parent=0);
private slots:
    void timerShot();
private:
    QTimer      *timer;
    QString     stylebutton;
    QString     str;
    QString     imgpath;
    QStringList colors;
    int         width;
    int         height;
    int         i;
    int         frames;
    void        mouseReleaseEvent(QMouseEvent *e);
};

#endif // MYBUTTON_H
