#include "tabdialog.h"
TabDialog::TabDialog(QString filepath, QWidget *parent):QDialog(parent){
    path    =filepath;
    clearbutton   = new MyButton(tr("Clear all"),this);
    deleteSelectedButton = new MyButton(tr("Delete selected"),this);
    goButton = new MyButton(tr("Go"),this);
    table   = new QTableWidget();
    lay     = new QGridLayout();
    li     <<"URL" <<"TITLE";
    row     =0;
    col     =1;
    //-------------------------------------------------------------------
    setWindowTitle(tr("Tabs"));
    setModal(true);
    setAttribute(Qt::WA_DeleteOnClose);//удаление диалога из памяти при закрытии
    setLayout(lay);
    //-------------------------------------------------------------------
    //начинаем читать файл загладок
    // Если файл успешно открыт для чтения в текстовом режиме
    //записываем в файл
    QFile file(path);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
     {
        QTextStream text(&file);
        while(!(text.atEnd())){
            lineTab = text.readLine();

            //Заполняем лист URL---------------------------------
            //удаляем тег <a href='<myURL>'>.>sssssss</a>...
            QString s = lineTab;

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
            s = lineTab;
            str=">";
            pos = s.indexOf(str,0);

            s.remove(0,pos+str.length());
            str="</a>";
            pos = s.indexOf(str,0);
            s.remove(pos,s.length());
            //отправляем отформатированный текст в список
            qDebug() <<"title="<<s;
            titleList << s;

            row++;


        }
        file.close(); // Закрываем файл
        //qDebug() << "Tablist.size():";
        //qDebug() << urlList.size();
     }

    //-------------------------------------------------------------------
    lay->addWidget(table);
    lay->addWidget(clearbutton);
    lay->addWidget(deleteSelectedButton);
    lay->addWidget(goButton);

    table->clear();
    table->setFixedWidth(600);

    table->setRowCount(row);
    table->setColumnCount(li.count());
    table->setHorizontalHeaderLabels(li);//установили заголовки li<<URL<<TITLE
    //table->hideColumn(1);
    //вставили новую запись
    //table->insertRow(table->rowCount());

    //пошли заполнять таблицу
    for(int i =0; i<table->rowCount();i++){
        //сделали активной
        table->setCurrentCell(table->rowCount()+i,0);

        url =urlList.at(i);
        title=titleList.at(i);
        //qDebug()<< "ADD url:"<<url;
        //qDebug()<< "ADD title:"<<title;

        table->setItem(table->currentRow()+i+1,0,new QTableWidgetItem(url));
        table->setItem(table->currentRow()+i+1,1,new QTableWidgetItem(title));
    }
    table->setColumnWidth(0,300);
    table->setColumnWidth(1,300);
    table->setRowCount(row);
    //--------------------------------------------------------------
    //connect(table,SIGNAL(cellClicked(int,int)),this,SLOT(TabCellClicked(int,int)));
    connect(clearbutton,SIGNAL(clicked(bool)),this,SLOT(ClearTabsClicked()));
    connect(deleteSelectedButton,SIGNAL(clicked(bool)),this,SLOT(DeleteSelectedCell()));
    connect(goButton,SIGNAL(clicked(bool)),this,SLOT(GoClicked()));

}

void TabDialog::TabCellClicked(int rowselected, int colselected)
{

    /*
    if (rowselected<row){
        //qDebug() << "rowselected="<<rowselected;

        //QString addr="www.google.com";
        QString addr=table->item(rowselected,0)->text();
        //qDebug() << addr;
        if (addr!=""){
            emit gotoUrl(addr);
        }
    }
    */
}

void TabDialog::ClearTabsClicked()
{
    table->clear();//очищаем таблицу
    table->setRowCount(0);
    table->setColumnCount(li.count());
    table->setHorizontalHeaderLabels(li);//установили заголовки
    //-------------------------------------------------------------------
    //начинаем читать файл истории
    //отчищаем файл истории
    QFile file(path);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
     {
        QTextStream out(&file);

        out << "";
        file.close(); // Закрываем файл
     }


}

void TabDialog::DeleteSelectedCell()
{
    int s=table->currentRow();
    table->removeRow(s);
    //-------------------------------------------------------------------
    //начинаем читать файл истории
    //отчищаем файл истории
    QFile file(path);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
     {
        QTextStream out(&file);

        out << " ";
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

void TabDialog::GoClicked()
{
    int indexrow=table->currentRow();

        QString addr=table->item(indexrow,0)->text();
        //qDebug() << addr;
        if (addr!=""){
            emit gotoUrl(addr);
        }

}

