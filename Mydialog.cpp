//SETTINGS DIALOG
#include "mydialog.h"

MyDialog::MyDialog(QSettings *mysettings, QWidget *parent=0):QDialog(parent)
{
    //-----------------------------------------------------------------------------
    //Инициализация
    settings = mysettings;

    //useProxyBox   = new QCheckBox();
    useProxyBox     = new MyCheckBox();

    hostEdit        = new QLineEdit();
    portEdit        = new QLineEdit();
    userEdit        = new QLineEdit();
    passEdit        = new QLineEdit();

    okButton        = new QPushButton(tr("ok"));
    cancelButton    = new QPushButton(tr("cancel"));
    defaultButton   = new QPushButton(tr("Load defaults"));

    lay             = new QGridLayout();

    //создаем регулярные выражения для имени хоста
    //https://www.ibm.com/developerworks/ru/library/l-regexp_1/index.html
    //+ эквивалент выражения \{1,\}
    //? эквивалент выражения \{0,1\}
    //| эквивалент выражения или
    //\{min,max\} уточнения количества повторений

    QString adr1    = "([0]{1})";//0
    QString adr2    = "([1]{1}[0-9]{0,2})";
    QString adr3    = "([1-9]{1,2})";//199
    QString adr4    = "([2]{1}[0-5]{0,2})";//255
    QString adr     ="("+adr1+"|"+adr2+"|"+adr3+"|"+adr4+")";
    QRegExp hostregExp(adr+"([.]+)"+adr+"([.]+)"+adr+"([.]+)"+adr);

    //регулярные выражения для порта
    QRegExp portregExp("[0-9]*");
    //-----------------------------------------------------------------------------
    passEdit->setEchoMode(QLineEdit::Password);//константа Password определена в классе QLineEdit// нажимаем кнопку и будет отклик на экране

    hostEdit->setEnabled(false);
    portEdit->setEnabled(false);
    userEdit->setEnabled(false);
    passEdit->setEnabled(false);

    useProxyBox->setChecked(settings->value("proxy/useProxy").toBool());
    hostEdit->setText(settings->value("proxy/host").toString());
    portEdit->setText(settings->value("proxy/port").toString());
    userEdit->setText(settings->value("proxy/user").toString());
    passEdit->setText(settings->value("proxy/password").toString());

    setWindowTitle(tr("Settings"));
    setModal(true);
    setAttribute(Qt::WA_DeleteOnClose);//удаление диалога из памяти при закрытии

    setLayout(lay);
    //Установка регулярных выражений
    hostEdit->setValidator(new QRegExpValidator(hostregExp,this));
    portEdit->setValidator(new QRegExpValidator(portregExp,this));
    //----------------------------------------------------
    lay->addWidget(useProxyBox,                     0,1);//[1 строка] [колонка 0] это положение в компоновщике
    lay->addWidget(hostEdit,                        1,1);
    lay->addWidget(portEdit,                        2,1);
    lay->addWidget(userEdit,                        3,1);
    lay->addWidget(passEdit,                        4,1);


    lay->addWidget(new QLabel(tr("Use proxy?")),    0,0);//[0 строка] [колонка 0] это положение в компоновщике
    lay->addWidget(new QLabel(tr("Hostname")),      1,0);
    lay->addWidget(new QLabel(tr("Port")),          2,0);
    lay->addWidget(new QLabel(tr("Username")),      3,0);
    lay->addWidget(new QLabel(tr("Password")),      4,0);

    lay->addWidget(okButton,                        5,0);
    lay->addWidget(cancelButton,                    5,1);
    lay->addWidget(defaultButton,                   6,0,1,2);//[rowspan] [colspan] - охват колонок(2) и охват строк(1)

    //---------------------------------------------------
    connect(okButton, SIGNAL(clicked(bool)),this,SLOT(okClicked(bool)));
    //connect(cancelButton, SIGNAL(clicked(bool)),this,SLOT(cancelClicked(bool)));
    connect(cancelButton, SIGNAL(clicked()),this,SLOT(reject()));
    connect(defaultButton, SIGNAL(clicked(bool)),this,SLOT(defaultClicked(bool)));
    connect(useProxyBox, SIGNAL(stateChanged(int)),this,SLOT(useCheckBoxChanged(int)));
    connect(hostEdit,SIGNAL(textChanged(QString)),this,SLOT(on_hostEdit_textChanged(QString)));
    connect(portEdit,SIGNAL(textChanged(QString)),this,SLOT(on_portEdit_textChanged(QString)));
    //испускание сигналов--------------------------------
    on_hostEdit_textChanged(hostEdit->text());
    useCheckBoxChanged(useProxyBox->checkState());
    //state - трехстабильный check box
    }


void MyDialog::setEnableLinesEdit(){}
//---------------------------------------------------
void MyDialog::okClicked(bool)
{
    settings->setValue("proxy/useProxy",useProxyBox->isChecked());
    settings->setValue("proxy/host",hostEdit->text());
    settings->setValue("proxy/port",portEdit->text());
    settings->setValue("proxy/user",userEdit->text());
    settings->setValue("proxy/password",passEdit->text());
    settings->sync();//синхронизация хранилища памяти с хранилищем на диске
    emit proxyChanged();//испускание сигнала
    close();
}
//---------------------------------------------------
void MyDialog::defaultClicked(bool)
{
    useProxyBox->setChecked(true);
    hostEdit->setText("172.27.100.5");
    portEdit->setText("444");
    userEdit->setText("student.istu");
    passEdit->setText("student");
}
//---------------------------------------------------
void MyDialog::useCheckBoxChanged(int state)
{
    if (state==Qt::Checked){

        hostEdit->setEnabled(true);
        portEdit->setEnabled(true);
        userEdit->setEnabled(true);
        passEdit->setEnabled(true);
        okButton->setEnabled(false);
    }
    else{
        hostEdit->setEnabled(false);
        portEdit->setEnabled(false);
        userEdit->setEnabled(false);
        passEdit->setEnabled(false);
        okButton->setEnabled(true);
    }
}

void MyDialog::on_hostEdit_textChanged(QString editLineText)
{
       qDebug() << editLineText;
       okButton->setEnabled(hostEdit->hasAcceptableInput());
}
void MyDialog::on_portEdit_textChanged(QString editLineText)
{
       qDebug() << editLineText;
       okButton->setEnabled(not(portEdit->text().isEmpty()));
}
