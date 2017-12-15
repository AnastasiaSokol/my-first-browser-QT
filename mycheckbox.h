#ifndef MYCHECKBOX_H
#define MYCHECKBOX_H
#include <QCheckBox>
#include <QTimer>

class MyCheckBox : public QCheckBox
{
    Q_OBJECT//макрос необходимо задавать в начале любого класса содержащего сигналы или слоты
public:
    MyCheckBox(QWidget *parent=0);
private:
    QTimer *timer;
    int colorIndex;
    void mouseReleaseEvent(QMouseEvent *e);
private slots:
    void timerShot();

};

#endif // MYCHECKBOX_H
