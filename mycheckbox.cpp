#include "mycheckbox.h"

MyCheckBox::MyCheckBox(QWidget *parent): QCheckBox(parent)
{
//Сделаем изменение цвета по таймеру
    //таймер посылаем сигналы через интервалы времени timeout
    timer = new QTimer(this);
    timer->setSingleShot(true);//однократное срабатываение =true
    connect(timer, SIGNAL(timeout()),this,SLOT(timerShot()));
    colorIndex=0;

    //SETTINGS-----------------------------------------------
    //политика установки размера
    setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Minimum);//чтобы не во всю ширину была
    //стили css
    setStyleSheet("padding: 15px 10px 15px 15px;");
}
void MyCheckBox::timerShot(){
    QStringList colors;
    colors << "96caf7" << "6fb2ed"<< "499ce5"
           << "23BBe0"<<"096cc1"<<"01549b"
           <<"efc734"<<"e8c751"<<"f7da71"<<"ffe99b";//<<-добавление в лист
    //Если последний цвет
    if (colorIndex==colors.length()-1){
        colorIndex=0;

    }
    //Если не последний цвет
    else{
        //стили css
        setStyleSheet("border: 5px dotted #"+colors.at(colorIndex)+";\
                       background: #"+colors.at(colors.length()-1-colorIndex)+";\
                       padding: 5px 0px 5px 5px;");
        colorIndex++;
        timer->start(100);//100ms
    }
}
//сигналы слоты и события это разные вещи
//систма событий обрабатывается компонентами
//у всех объетов Qt есть стандартные методы обработки событий
void MyCheckBox::mouseReleaseEvent(QMouseEvent *e){

    timer->start(100);//100ms
    //обращаемся к чему то что находится в области видимости QCheckBox
    //пространство имен
    QCheckBox::mouseReleaseEvent(e);//передаем событие в
}
