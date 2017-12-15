#ifndef MYMENU_H
#define MYMENU_H

#include <QMenu>
#include <QTimer>

class MyMenu : public QMenu
{
    Q_OBJECT//макрос необходимо задавать в начале любого класса содержащего сигналы или слоты
public:
    MyMenu(QString text, QWidget *parent=0);
private:
    QTimer      *timer;
    QTimer      *timerwaitmenu;
    QString     style;
    QString     str;
    QStringList colors;
    int         width;
    int         height;
    int         i;
    int         indexcolor;
    int         frames;
    void        mouseReleaseEvent(QMouseEvent *e);
private slots:
    void timerShot();
    void closeMenu();

};
#endif // MYMENU_H
