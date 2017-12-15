#include "histordialog.h"
HistorDialog::HistorDialog(QString filepath, QWidget *parent):QDialog(parent){
    myfilepath=filepath;
    clearhistorybutton   = new MyButton(tr("Clear all"),this);
    deleteSelectedButton = new MyButton(tr("Delete selected"),this);
    table   = new QTableWidget();
    lay     = new QGridLayout();
    BoxPeriod = new QComboBox(this);

    li          <<tr("URL") <<tr("TITLE")<<tr("TIME")<<tr("DATE");
    periodsList << tr("Today")<<tr("yesterday")<<tr("All time");

    row     =0;
    col     =li.length();
    //-------------------------------------------------------------------
    setWindowTitle(tr("History"));
    setModal(true);
    setAttribute(Qt::WA_DeleteOnClose);//удаление диалога из памяти при закрытии
    setLayout(lay);
    //-------------------------------------------------------------------
    //начинаем читать файл истории
    // Если файл успешно открыт для чтения в текстовом режиме
    //записываем в файл
    // Если файл не открывается то создается заново пустым
    QFile filehistory(myfilepath);
    if(filehistory.open(QIODevice::ReadOnly | QIODevice::Text))
     {
        QTextStream textfromfilehistory(&filehistory);
        //textfromfilehistory(&filehistory); // Создаем объект класса QTextStream

        //то проходим по каждой строке пока файл не закончится чтобы посчитать количество записей
        while(!(textfromfilehistory.atEnd())){
            linehistory = textfromfilehistory.readLine();

            //Заполняем лист URL---------------------------------
            //удаляем тег <a href='<myURL>'>....
            QString s = linehistory;
            QString str="href='";
            int pos = s.indexOf(str,0);
            s.remove(0,pos+str.length());
            str="'>";
            pos = s.indexOf(str,0);
            s.remove(pos,s.length());
            //отправляем отформатированный текст в список
            //qDebug() <<"url="<<s;
            urlList << s;

            //Заполняем лист заголовков---------------------------
            //удаляем тег <a href='<myURL>'> <myTitle> </...
            s = linehistory;
            str=">";
            pos = s.indexOf(str,0);

            s.remove(0,pos+str.length());
            str="</a>";
            pos = s.indexOf(str,0);
            s.remove(pos,s.length());
            //отправляем отформатированный текст в список
            //qDebug() <<"title="<<s;
            titleList << s;

            //Заполняем лист времени-----------------------------
            s = linehistory;
            str="time:";
            pos = s.indexOf(str,0);
            s.remove(0,pos+str.length());

            str="date";
            pos = s.indexOf(str,0);
            s.remove(pos,s.length());
            //отправляем отформатированный текст в список
            //qDebug() <<"time="<<s;
            timeList << s;

            //Заполняем лист даты-----------------------------
            s = linehistory;
            str="date:";
            pos = s.indexOf(str,0);
            s.remove(0,pos+str.length());

            str="</font>";
            pos = s.indexOf(str,0);
            s.remove(pos,s.length());
            //отправляем отформатированный текст в список
            qDebug() <<"date="<<s;
            dateList << s;

            row++;


        }
        filehistory.close(); // Закрываем файл

        qDebug() << "ROW:";
        qDebug() << row;
        qDebug() << "historylist.size():";
        qDebug() << urlList.size();
     }
    //------------------------------------------------------------------
    BoxPeriod->addItems(periodsList);
    BoxPeriod->setCurrentIndex(periodsList.length()-1);
    //-------------------------------------------------------------------
    lay->addWidget(table);
    lay->addWidget(clearhistorybutton);
    lay->addWidget(deleteSelectedButton);
    lay->addWidget(BoxPeriod);
    //-------------------------------------------------------------------
    table->clear();
    table->setFixedWidth(600);
    table->setRowCount(row);
    table->setColumnCount(li.count());
    table->setHorizontalHeaderLabels(li);//установили заголовки

    for(int i =0; i<table->rowCount();i++){
        //сделали активной
        table->setCurrentCell(table->rowCount()+i,0);
        //table->setCurrentCell(i,0);

        url =urlList.at(row-i-1);
        title=titleList.at(row-i-1);
        time=timeList.at(row-i-1);
        date=dateList.at(row-i-1);

        //qDebug()<< "ADD url:"<<url;
        //qDebug()<< "ADD title:"<<title;
        //url =myhistory->itemAt(i).url().toString();
        table->setItem(table->currentRow()+i+1,0,new QTableWidgetItem(url));
        table->setItem(table->currentRow()+i+1,1,new QTableWidgetItem(title));
        table->setItem(table->currentRow()+i+1,2,new QTableWidgetItem(time));
        table->setItem(table->currentRow()+i+1,3,new QTableWidgetItem(date));
    }
    table->setColumnWidth(0,300);
    table->setColumnWidth(1,300);
    table->setRowCount(row);
    //--------------------------------------------------------------
    connect(table,SIGNAL(cellClicked(int,int)),this,SLOT(HistorCellClicked(int,int)));
    connect(clearhistorybutton,SIGNAL(clicked(bool)),this,SLOT(ClearHistorClicked()));
    connect(deleteSelectedButton,SIGNAL(clicked(bool)),this,SLOT(DeleteSelectedCell()));
    connect(BoxPeriod,SIGNAL(currentIndexChanged(int)),this,SLOT(ShowForPeriod(int)));

}

void HistorDialog::HistorCellClicked(int rowselected, int colselected)
{


    if (rowselected<row){
        qDebug() << "rowselected="<<rowselected;

        //QString addr="www.google.com";
        QString addr=table->item(rowselected,0)->text();
        qDebug() << addr;
        if (addr!=""){
            emit gotUrl(addr);
        }
    }
}

void HistorDialog::ClearHistorClicked()
{
    table->clear();//очищаем таблицу
    table->setRowCount(0);
    table->setColumnCount(li.count());
    table->setHorizontalHeaderLabels(li);//установили заголовки
    //-------------------------------------------------------------------
    //начинаем читать файл истории
    //отчищаем файл истории
    QFile filehistory(myfilepath);
    if(filehistory.open(QIODevice::WriteOnly | QIODevice::Text))
     {
        QTextStream out(&filehistory);
        out << " ";
        filehistory.close(); // Закрываем файл
     }

}
void HistorDialog::DeleteSelectedCell()
{
    int s=table->currentRow();
    table->removeRow(s);
    //-------------------------------------------------------------------
    //начинаем читать файл истории
    //отчищаем файл истории
    QFile file(myfilepath);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
     {
        QTextStream out(&file);
        out << "";
        file.close(); // Закрываем файл
     }
    //-------------------------------------------------------------------
    //заполняю данными из таблицы
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
     {
        QTextStream in(&file);
        for (int i=0;i<table->rowCount();i++){
            //url
            QString itemTextURL = table->item(i,0)->text();
            QString itemTextTitle = table->item(i,1)->text();
            in   <<"<a href='"
                 << itemTextURL
                 <<"'>"
                 << itemTextTitle
                 <<"</a>"
                 <<"<br>"
                 <<"\n";// Посылаем строку в поток для записи
        }

        file.close(); // Закрываем файл
     }

}

void HistorDialog::ShowForPeriod(int index)
{
   //today
   if (index==0) {
       QDateTime current = QDateTime::currentDateTime();

       table->clear();//очищаем таблицу
       int j=0;

       table->setColumnCount(li.count());

       table->setHorizontalHeaderLabels(li);//установили заголовки
       for(int i =0; i<row;i++){

           //table->setCurrentCell(j,0);//сделали активной

           url =urlList.at(row-i-1);
           title=titleList.at(row-i-1);
           time=timeList.at(row-i-1);
           date=dateList.at(row-i-1);

           int day = current.date().day();
           int month = current.date().month();
           int year = current.date().year();

           QString d = QString::number(day);
           QString m = QString::number(month);
           QString y = QString::number(year);

           QString currentDate= d.append('.');
           currentDate = currentDate.append(m);
           currentDate = currentDate.append('.');
           currentDate = currentDate.append(y);

           qDebug() <<"currentDate"<<currentDate;
           qDebug() <<"date"<<date<<" time"<<time << "QURL"<<url;

           if (date==currentDate) {
               qDebug() <<"yes";
               table->setRowCount(j+1);
               table->setItem(j,0,new QTableWidgetItem(url));
               table->setItem(j,1,new QTableWidgetItem(title));
               table->setItem(j,2,new QTableWidgetItem(time));
               table->setItem(j,3,new QTableWidgetItem(date));
               j++;
           }
           else{
               qDebug() <<"no";
           }

       }
   }
   else{
       //yesterday
       if (index==1){
           QDateTime yesterday = QDateTime::currentDateTime();
           table->clear();//очищаем таблицу
           int j=0;
           table->setColumnCount(li.count());
           table->setHorizontalHeaderLabels(li);//установили заголовки
           for(int i =0; i<row;i++){

               url =urlList.at(row-i-1);
               title=titleList.at(row-i-1);
               time=timeList.at(row-i-1);
               date=dateList.at(row-i-1);

               int month = yesterday.date().month();
               int year = yesterday.date().year();
               int day = yesterday.date().day();
               //текущую дату превращаем во вчерашнюю------------------------

               //если это не первый   день в месяце
               if (day!=1){
                   day--;
               }
               //если это первый день месяца
               else{
                   //если это не первый месяц в году
                   if (month!=1){
                       month--;
                       //найти последний день  в месяце
                       QDate dat(year, month, day);
                       int countofdayofmonth = dat.daysInMonth();
                       day = countofdayofmonth;
                   }
                   //если это первый месяц в году
                   else{
                       year--;
                       month=12;
                       //ищем последний день в последнем месяце
                       QDate n(year, month, day);
                       int countofdayofmonth = n.daysInMonth();
                       day = countofdayofmonth;
                   }
               }


               QString d = QString::number(day);
               QString m = QString::number(month);
               QString y = QString::number(year);

               QString currentDate= d.append('.');
               currentDate = currentDate.append(m);
               currentDate = currentDate.append('.');
               currentDate = currentDate.append(y);

               qDebug() <<"currentDate"<<currentDate;
               qDebug() <<"date"<<date<<" time"<<time << "QURL"<<url;

               if (date==currentDate) {
                   qDebug() <<"yes";
                   table->setRowCount(j+1);
                   table->setItem(j,0,new QTableWidgetItem(url));
                   table->setItem(j,1,new QTableWidgetItem(title));
                   table->setItem(j,2,new QTableWidgetItem(time));
                   table->setItem(j,3,new QTableWidgetItem(date));
                   j++;
               }
               else{
                   qDebug() <<"no";
               }

           }
       }
       else {
           //all time
           if(index==2){
               table->clear();//очищаем таблицу
               int j=0;
               table->setColumnCount(li.count());
               table->setHorizontalHeaderLabels(li);//установили заголовки

               for(int i =0; i<row;i++){

                   url =urlList.at(row-i-1);
                   title=titleList.at(row-i-1);
                   time=timeList.at(row-i-1);
                   date=dateList.at(row-i-1);


                  table->setRowCount(j+1);
                  table->setItem(j,0,new QTableWidgetItem(url));
                  table->setItem(j,1,new QTableWidgetItem(title));
                  table->setItem(j,2,new QTableWidgetItem(time));
                  table->setItem(j,3,new QTableWidgetItem(date));
                  j++;
               }

           }

       }

   }
}

