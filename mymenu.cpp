#include "mymenu.h"

MyMenu::MyMenu(QString text, QWidget *parent): QMenu(parent)
{
    //initialize--------------------------------------------------
     timer         = new QTimer(this);
     timerwaitmenu = new QTimer(this);
     width         = 180;
     height        = 0;
     indexcolor    = 0;
     i             = 0;
     frames        = 20;//количество кадров анимации
     style         =
             "background-color: #f2f2f2;\
             text-align:center;\
             text-decoration:none;\
             border-width: 1px;\
             border-color: #5a5a5a;\
             border-style:solid;\
             padding: 2px;\
             font-weight:bold;\
             color: #5a5a5a;\
             width:"+(QString::number(width))+"px;\
             height:"+(QString::number(height))+"px;\
             ";

    colors << "5a5a5a" << "724d4d"<< "844343" << "ba2525"<<"ea0b0c"
           <<"f80404"  <<"ea0b0c" <<"ba2525"  <<"844343" <<"5a5a5a";//<<-добавление в лист
     //settings---------------------------------------------------
     setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Minimum);//чтобы не во всю ширину была
     setTitle(text);
     setStyleSheet(style);
     timer          ->setSingleShot(true);//одноразовое срабатывание
     timerwaitmenu  ->setSingleShot(true);//одноразовое срабатывание
     //connection-------------------------------------------------
    connect(timer, SIGNAL(timeout()),this,SLOT(timerShot()));
    connect(timerwaitmenu, SIGNAL(timeout()),this,SLOT(closeMenu()));

}
void MyMenu::mouseReleaseEvent(QMouseEvent *e)
{
    timer->start(25);//100ms
    QMenu::mouseReleaseEvent(e);//передаем событие в
}

void MyMenu::timerShot()
{
    if (i==frames){
        i          = 0;
        indexcolor = 0;
        //width      = 180;
        height     = 160;
        str        = style+
                "color: #"+colors.at(indexcolor)+";\
                 height:"+(QString::number(height))+"px;\
                ";
        setStyleSheet(str);
        timerwaitmenu->start(5000);//10ms
    }
    else{
        if(i==0){width=200;}else {width--;}
        if (i % 10 ==0){ indexcolor =0;}else{indexcolor++;}
        /*
        if (i<=(frames % 2)){
            width++;
        }
        else{
            width--;
        }*/


        if (i==0){ height=0;}else{height=height+8;}
        str=style+
                "color: #"+colors.at(indexcolor)+";\
                 width:"+(QString::number(width))+"px;\
                 height:"+(QString::number(height))+"px;\
                ";
        setStyleSheet(str);
        i++;

        timer->start(25);//задержка между изменениями 25ms
    }


}

void MyMenu::closeMenu()
{
    //qDebug() << "CloseMenu";
    width=180;
    height=0;
    str=style+
            "width:"+(QString::number(width))+"px;\
            height:"+(QString::number(height))+"px;\
            ";
    setStyleSheet(str);
}
