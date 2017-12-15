#include "mybutton.h";


MyButton:: MyButton(QString text, QWidget *parent): QPushButton(parent){

   //initialize--------------------------------------------------
    width = 150;
    height =15;
    imgpath="main_menu.jpg";
    frames  =10;//количество кадров анимации
    timer = new QTimer(this);
    //url('"+imgpath+"') repeat
    stylebutton=
            "background-color: #009688;\
            text-align:center;\
            text-decoration:none;\
            border-width: 1px;\
            border-color: #817164;\
            border-style:solid;\
            padding: 2px;\
            font-weight:bold;\
            color: #dbf4f2;\
            width:"+(QString::number(width))+"px;\
            height:"+(QString::number(height))+"px;\
            ";

   i=0;
   colors << "dbf4f2" << "fdc6c6"<< "fd8686" << "fb4646"<<"ff1313"
          <<"ff1313"  <<"fb4646" <<"fd8686"  <<"fdc6c6" <<"dbf4f2";//<<-добавление в лист
    //settings---------------------------------------------------
    setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Minimum);//чтобы не во всю ширину была
    setText(text);
    setStyleSheet(stylebutton);
    timer->setSingleShot(true);//одноразовое срабатывание
    //connection-------------------------------------------------
    connect (timer, SIGNAL(timeout()),this,SLOT(timerShot()));
}
void MyButton::timerShot(){
    //qDebug() << "timeout";
    if (i==frames){
        i=0;
        width = 150;
        str=stylebutton+
                "color: #"+colors.at(frames-1-i)+";\
                 width:"+(QString::number(width))+"px;\
                ";
        setStyleSheet(str);
    }
    else{
        //qDebug() << i;
        if (i<=5){
            width++;
        }
        else{
            width--;
        }
        //str=stylebutton+"color: #"+colors.at(frames-1-i)+";";
        str=stylebutton+
                "color: #"+colors.at(frames-1-i)+";\
                 width:"+(QString::number(width))+"px;\
                ";
        setStyleSheet(str);
        i++;
        timer->start(25);//задержка между изменениями 25ms
    }
}

void MyButton::mouseReleaseEvent(QMouseEvent *e){
    // qDebug() << "comeback";
    timer->start(25);//100ms
    QPushButton::mouseReleaseEvent(e);//передаем событие в

}
