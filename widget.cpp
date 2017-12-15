//MAIN DIALOG IF OUR BRAUSER
#include "widget.h"//файл в директории проекта
//#include "mydialog.h"
//#include "histordialog.h"


#ifdef Q_OS_WIN32
    #define _WIN32_IE 0x0400
    #include <shlobj.h>
    #undef _WIN32_IE
#endif
//файл реализации
Widget::Widget(QWidget *parent)//реализация конструтора
    : QWidget(parent)
{
    //----------------------------------------------------------------------------------
    //QStackedWidget
    /*Попытка со вкладками не удалась удалаяй
     * то что закомменчено
    QPushButton *firstPageWidget  = new QPushButton(tr("first"));
    QPushButton *secondPageWidget = new QPushButton(tr("second"));
    QPushButton *thirdPageWidget  = new QPushButton(tr("treath"));

    QTabWidget *stackedWidget     = new QTabWidget;

    stackedWidget->addTab(firstPageWidget,"1");
    stackedWidget->addTab(secondPageWidget,"2");
    stackedWidget->addTab(thirdPageWidget,"+");
    stackedWidget->setTabIcon(0,QIcon("icon.png"));
    */
    //----------------------------------------------------------------------------------
    //путь к файлу истории
    filepathtab       = "tag.html";
    filepathhistory   = "history.html";
    //адресс страницы
    adresstr          = new QLineEdit();
    //кнопки управления
    //prevbutton1     = new MyButton(tr("<<"),this);
    //nextbutton2     = new MyButton(tr(">>"),this);
    //stopbutton3     = new MyButton(tr("stop"),this);
    //refreshbutton4  = new MyButton(tr("refresh"),this);
    //gobutton5       = new MyButton(tr("go"),this);
    //страница отображения
    webView           = new QWebView();

    //создадим меню
    menuBar           = new QMenuBar();
    mainMenu          = new MyMenu("",this);
    goAction          = new QAction(this);
    backAction        = new QAction(this);
    reloadAction      = new QAction(this);
    tabAction         = new QAction(this);

    settingsAction    = new QAction(tr("Settings"),this);
    closeAction       = new QAction(tr("Close"),this);
    historyAction     = new QAction(tr("History"),this);
    showOurTabsAction = new QAction(tr("Tabs"),this);

    //Для масштабирования
    spinboxScale      = new QSpinBox;//счетчик
    sliderScale       = new QSlider(Qt::Horizontal);  //горизонтальный бегунок
    labelScale        = new QLabel(tr(""));

    //компоновщик layout -расскладывает на формочке ГЭ. gridlayot - в виде таблицы
    mainlay1          = new QVBoxLayout();
    innerlay1         = new QVBoxLayout();
    toolbarlay2       = new QHBoxLayout();//Horisontal
    layScale          = new QHBoxLayout();
    StatusBarLay      = new QHBoxLayout();

    //Строка состояния
    labelCondition    = new QLabel(tr("Status Bar"));

    //----------------------------------------------------------------------------------
    //Settings
    setWindowTitle(tr("My brauser"));
    this->setWindowIcon(QIcon("icon.png"));
            //кнопки их доступность------------------------------------------------------------
            //prevbutton1     ->setEnabled(false);
            //nextbutton2     ->setEnabled(false);
            //stopbutton3     ->setEnabled(false);
            //refreshbutton4  ->setEnabled(false);

            //всплывающие подсказки------------------------------------------------------------
            //prevbutton1     ->setToolTip(tr("Нажмите, чтобы вернуться  назад"));
            //nextbutton2     ->setToolTip(tr("Нажмите, чтобы перейти вперед"));
            //stopbutton3     ->setToolTip(tr("Нажмите, чтобы остановить загрузку страницы"));
            //refreshbutton4  ->setToolTip(tr("Нажмите, чтобы обновить страницу"));
            //gobutton5       ->setToolTip(tr("Нажмите, чтобы перейти по URL"));

            spinboxScale    ->setToolTip(tr("Page Zoom"));
            settingsAction  ->setToolTip(tr("Change proxy settings"));
            closeAction     ->setToolTip(tr("Quite"));
            goAction        ->setToolTip(tr("Go to URL"));
            backAction      ->setToolTip(tr("Go back"));
            reloadAction    ->setToolTip(tr("Reload page"));
            tabAction       ->setToolTip(tr("Click if want add this page i favourite"));
            historyAction   ->setToolTip(tr("Show my history"));
            showOurTabsAction->setToolTip(tr("Show my favourite pages"));


    //меню установка картинок----------------------------------------------------------------------------
    mainMenu        ->setToolTipsVisible(true);//видимость подсказок
    menuBar         ->setStyleSheet("background:#f2f2f2;");
    mainMenu        ->setIcon(QIcon("custom.png"));
    goAction        ->setIcon(QIcon("go.png"));
    backAction      ->setIcon(QIcon("back.png"));
    reloadAction    ->setIcon(QIcon("reload.png"));
    tabAction       ->setIcon(QIcon("tab.png"));
    QPixmap pix("scale.png");
    QPixmap newPix = pix.scaled(QSize(20,20),  Qt::KeepAspectRatio);//pix.scaled(15,10,Qt::IgnoreAspectRatio,Qt::FastTransformation);
    labelScale      ->setPixmap(newPix);
    //установка элементов масштабирования----------------------------------------------
    spinboxScale    ->setRange(1,200);   //допустимый диапазон изменений ползунка
    spinboxScale    ->setValue(100);
    spinboxScale    ->setSingleStep(1);
    sliderScale     ->setRange(1,200);    //допустимый диапазон изменений счетчика
    sliderScale     ->setValue(100);
    //устанавливаем политику масштабирования------------------------------------------
    //menuBar       ->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);//по горизонтально расширяем максимального, по вертикали ограничиваем Expanding
    menuBar         ->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);//по горизонтально расширяем максимального, по вертикали ограничиваем Expanding
    webView         ->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);//по горизонтально расширяем максимального, по вертикали ограничиваем Expanding

    //загрузка страницы
    webView         ->load(QUrl("http://txt.newsru.com"));

    //Это свойство утанавливается, как QWebPage должен делегировать обработку ссылок через сигнал linkClicked ().
    // DontDelegateLinks - Никакие ссылки не делегированы. Вместо этого QWebPage пытается обрабатывать их все.
    //DelegateExternalLinks  При активации ссылок, указывающих на документы, которые не хранятся в локальной файловой системе или эквивалент - например, в системе ресурсов Qt, вызывается ссылкаClicked ().
    //DelegateAllLinks - Всякий раз, когда ссылка активирована, вызывается сигнал linkClicked ().
    webView         ->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);//передача по ссылкам

    //установки для компановщиков-------------------------------------------------------
    innerlay1       ->setContentsMargins(5,0,5,5);//поля внутри компановщика
    mainlay1        ->setMargin(0);//отступы аналог setContentsMargins(0,0,0,0);
    setLayout(mainlay1);//устанавливает компоновщик
    //----------------------------------------------------------------------------------
    //Коструирование интерфейса
    toolbarlay2->addWidget(menuBar);
    //toolbarlay2->addWidget(adresstr);

    /*
    toolbarlay2->addWidget(prevbutton1);
    toolbarlay2->addWidget(nextbutton2);
    toolbarlay2->addWidget(stopbutton3);
    toolbarlay2->addWidget(refreshbutton4);
    toolbarlay2->addWidget(gobutton5);
    */

    mainMenu    ->addAction(historyAction);
    mainMenu    ->addAction(showOurTabsAction);
    mainMenu    ->addAction(settingsAction);
    mainMenu    ->addAction(closeAction);

    menuBar     ->addMenu(mainMenu);
    menuBar     ->addAction(backAction);
    menuBar     ->addAction(goAction);
    menuBar     ->addAction(reloadAction);
    menuBar     ->addAction(tabAction);

    innerlay1   ->addLayout(toolbarlay2);
    //innerlay1   ->addWidget(stackedWidget);
    innerlay1   ->addWidget(webView);

    //конcтруирование элементов для масштабирования
    layScale    ->addWidget(labelScale);
    layScale    ->addWidget(spinboxScale);
    layScale    ->addWidget(sliderScale);
    layScale    ->addStretch(2);

    StatusBarLay->addWidget(labelCondition);

    //mainlay1    ->addWidget(menuBar);
    mainlay1    ->addLayout(toolbarlay2);
    mainlay1    ->addWidget(adresstr);
    mainlay1    ->addLayout(innerlay1);
    mainlay1    ->addLayout(StatusBarLay);
    mainlay1    ->addLayout(layScale);
    //----------------------------------------------------------------------------------
    connect(adresstr,       SIGNAL(returnPressed()),    this,   SLOT(goURL()));

   //connect(gobutton5,      SIGNAL(clicked(bool)),      this,   SLOT(goURL()));
   // connect(prevbutton1,    SIGNAL(clicked(bool)),      this,   SLOT(PrevButtonclicked()));
   // connect(nextbutton2,    SIGNAL(clicked(bool)),      this,   SLOT(NextButtonclicked()));
   // connect(refreshbutton4, SIGNAL(clicked(bool)),      this,   SLOT(RefreshButtonclicked()));
   // connect(stopbutton3,    SIGNAL(clicked(bool)),      this,   SLOT(StopButtonclicked()));

    connect(webView,        SIGNAL(linkClicked(QUrl)),      this,   SLOT(pageLinkClicked(QUrl)));
    connect(webView,        SIGNAL(titleChanged(QString)),  this,   SLOT(pageTitleChanged(QString)));
    connect(webView,        SIGNAL(urlChanged(QUrl)),       this,   SLOT(pageUrlChanged(QUrl)));


    connect(webView,        SIGNAL(loadStarted()),          this,   SLOT(pageLoadStarted()));
    connect(webView,        SIGNAL(loadFinished(bool)),     this,   SLOT(pageLoadFinished()));

    connect(closeAction,    SIGNAL(triggered(bool)),        this,   SLOT(closeClicked()));
    connect(settingsAction, SIGNAL(triggered(bool)),        this,   SLOT(settingsClicked()));
    connect(historyAction,  SIGNAL(triggered(bool)),        this,   SLOT(historyClicked()));
    connect(goAction,       SIGNAL(triggered(bool)),        this,   SLOT(NextButtonclicked()));
    connect(backAction,     SIGNAL(triggered(bool)),        this,   SLOT(PrevButtonclicked()));
    connect(reloadAction,   SIGNAL(triggered(bool)),        this,   SLOT(RefreshButtonclicked()));
    connect(tabAction,      SIGNAL(triggered(bool)),        this,   SLOT(favoriteButtonClicked()));
    connect(showOurTabsAction, SIGNAL(triggered(bool)),     this,   SLOT(showTabsClicked()));


    //синхонизация работы счетчика и ползунка:заставим счетчик и ползунок показывать одинаковые значения
    connect(spinboxScale, SIGNAL(valueChanged(int)),sliderScale, SLOT(setValue(int)));
    connect(spinboxScale, SIGNAL(valueChanged(int)),this, SLOT(changePageScale(int)));
    connect(sliderScale,  SIGNAL(valueChanged(int)),spinboxScale,SLOT(setValue(int)));
    //----------------------------------------------------------------------------------
    openSettings();
}

Widget::~Widget()//реализация деструктора
{
//закрытие устройст - ком портов например, удаление окна из памяти
    //деструктор необязательно может быть
    //потому что уборка мусора здесь автоматическая
}
//---------------------------------------------

//при клике на кнопку вызывать этот слот и получать URL
//проверять начинается ли адресс с http
void Widget::goURL(){
    QString addr = adresstr->text();

        if (!(addr.startsWith("http://")||addr.startsWith("https://"))){
            addr="http://"+addr;
        }
         webView->load(QUrl(addr));
    qDebug() << addr;

}


void Widget::goURLFromHistory(QString url){
    QString addr = url;
    if (!(addr.startsWith("http://")||addr.startsWith("https://"))){
        addr="http://"+addr;
    }
     qDebug() << addr;
     webView->load(QUrl(addr));
}

void Widget::goURLFromTabDialog(QString url)
{
    QString addr = url;
    if (!(addr.startsWith("http://")||addr.startsWith("https://"))){
        addr="http://"+addr;
    }
     qDebug() << addr;
     webView->load(QUrl(addr));
}
//---------------------------------------------

//меняем доступность кнопок при загрузке страницы
void Widget::pageLoadStarted (){
    //stopbutton3->setEnabled(true);
    //refreshbutton4->setEnabled(true);

    reloadAction->setIcon(QIcon("reload.png"));
    labelCondition->setText(tr("Page load started"));
}

void Widget::pageLoadFinished (){
    labelCondition->setText(tr("Page load finished"));
    //-----------------------------------------
    //stopbutton3->setEnabled(false);
    //-----------------------------------------
    //записываем в файл историю

    //если мы НЕ МОЖЕМ идти вперед
    //или
    //если мы МОЖЕМ идти вперед, но впереди не такой url как на тот на
    //который мы переходим
    if(
            (!(webView->history()->canGoForward())) //or
           // ((webView->history()->canGoForward())and(webView->history()->forwardItem().url()!=pURL))

     ){
        //-----------------------------------------
        //записываем в файл историю
        myfile = new QFile(filepathhistory);
        QDateTime current = QDateTime::currentDateTime();
        // Если файл успешно открыт для записи в текстовом режиме
        //дозаписываем его

        if(myfile->open(QIODevice::Append | QIODevice::Text))
         {
             QTextStream text(myfile); // Создаем объект класса QTextStream

             text             <<"<a href='"
                              << webView->url().toString()
                              <<"'>"
                              << webView->title()
                              <<"</a>"
                              <<"<font size='2' color='green' face='Arial'>"
                              <<"time:"
                              <<current.time().toString()
                              <<" date:"
                              <<current.date().day()
                              <<"."
                              <<current.date().month()
                              <<"."
                              <<current.date().year()
                              <<"</font>"
                              <<"<br>"
                              <<"\n";// Посылаем строку в поток для записи
             //qDebug()<<"history add ------";
             myfile->close(); // Закрываем файл
         }

    }

}
//---------------------------------------------

void Widget::changePageScale(int value)
{
    qDebug() << (qreal)(value)/100.0;
    webView->setZoomFactor((qreal)((value)/100.0));
    //QString str = QString::number( value );
    //qDebug() << "zoom:"+str+"%;";
    //setStyleSheet("size: "+str+"%;");
    //setStyleSheet("background-img:red;");

}
//-----------------------------------------------

void Widget:: pageLinkClicked(QUrl addr){
    webView->load(QUrl (addr));
    labelCondition->setText("Page link url["+addr.toString()+"] clicked");
}
//----------------------------------------------

void Widget::mySlot(){

}
//---------------------------------------------

void Widget::pageTitleChanged(QString title){
    QString titleOut = tr("My brauser");
    if(title.length()>0){
        titleOut +=" :: "+title;
    }
    setWindowTitle(titleOut);

}
//---------------------------------------------

void Widget::pageUrlChanged (QUrl pURL){
    adresstr->setText(pURL.toString());
    //разблакируем наши кнопки--------------------------

    //prevbutton1->setEnabled(webView->history()->canGoBack());
    //nextbutton2->setEnabled(webView->history()->canGoForward());

    //блокируем пункты меню-----------------------------
    backAction->setEnabled(webView->history()->canGoBack());
    goAction->setEnabled(webView->history()->canGoForward());

    if(!(backAction->isEnabled())){
        backAction->setIcon(QIcon("backnotenable.png"));
    }
    else{
         backAction->setIcon(QIcon("back.png"));
    }

     if(!(goAction->isEnabled())){
        goAction->setIcon(QIcon("gonotenable.png"));
     }
     else{
        goAction->setIcon(QIcon("go.png"));
     }


}
//---------------------------------------------

void Widget::PrevButtonclicked (){
    webView->back();
    qDebug() <<"current url: "<< webView->history()->currentItem().url();
}
void Widget::NextButtonclicked (){
    webView->forward();
}
void Widget::RefreshButtonclicked (){
    qDebug() << "refresh";//видно только в отладке в релиазе это исчезнет
    webView->reload();
}
void Widget::StopButtonclicked (){
    webView->stop();
}
void Widget::favoriteButtonClicked(){

    QFile myFile(filepathtab);
    QTextStream stream(&myFile); // Создаем объект класса QTextStream

    if (myFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        QString str = webView->url().toString();
        QString str1 =stream.readAll();
        if (str1.contains(str, Qt::CaseInsensitive)){
            //без учета регистра
            qDebug() << "yes";
        }
        else {
            myFile.close();
            if (myFile.open(QIODevice::Append | QIODevice::Text)){
            stream << "<a href='"
                   <<webView->url().toString()
                   <<"'>"
                   <<webView->title()
                   <<"</a>"
                   <<"<br>"
                   <<"\n";
                    myFile.close(); // Закрываем файл
            }
            qDebug()<<"no";
        }
    }
}


void Widget::closeClicked (){
    close();
}
//--------------------------------------

void Widget::settingsClicked (){
    MyDialog *settingsDialog = new MyDialog(settings,this);
    settingsDialog->show();
    connect(settingsDialog,SIGNAL(proxyChanged()),this,SLOT(loadSettings()));
}

void Widget::historyClicked()
{   
   //---------------------------------
   //открываем окно отображающее нашу историю
   //диалог истории
    historyD        = new HistorDialog(filepathhistory, 0);
    historyD->show();
    connect(historyD,SIGNAL(gotUrl(QString)),this,SLOT(goURLFromHistory(QString)));
}

void Widget::showTabsClicked()
{
   qDebug() <<"showTabsClicked";
   //---------------------------------
   //открываем окно отображающее нашу историю
   //диалог истории
   tabD        = new TabDialog(filepathtab, 0);
   tabD->show();
   connect(tabD,SIGNAL(gotoUrl(QString)),this,SLOT(goURLFromTabDialog(QString)));


}

void Widget::saveHistory(QUrl)
{

}
//--------------------------------------

void Widget::openSettings (){
    QString settingsPath = "./";
#ifdef Q_OS_WIN32
    wchar_t commonAppDataPath[MAX_PATH];
    if (SHGetSpecialFolderPath(0, commonAppDataPath, CSIDL_COMMON_APPDATA, FALSE)) {
       settingsPath = QString::fromWCharArray(commonAppDataPath)+QDir::separator()+
               "MyBrowserISTU2017"+QDir::separator();
       if (!QDir(settingsPath).exists()) {
           QDir(QString::fromWCharArray(commonAppDataPath)).mkpath(settingsPath);
           }
       }
#endif

    //Класс QSettings предоставляет постоянные платформонезависимые настройки приложения
    //Обычно пользователи ожидают, что приложение будет запоминать свои настройки (размеры и позиции окон, параметры и т.д.) между сессиями. Эта информация часто сохраняется в системном реестре в Windows и в файлах настроек XML в Mac OS X. В Unix-системах, в отсутствии стандарта, большинство приложений (включая приложения KDE) используют текстовые INI-файлы.
    //QSettings - это абстракция вокруг этих технологий, позволяющая сохранить и восстановить настройки приложения переносимым способом. Он также поддерживает пользовательские форматы хранения.
    // API QSettings основан на QVariant, позволяя вам с минимумом усилий сохранять большинство типов, основанных на значениях, таких как QString, QRect и QImage.
    //Если всё, что вам нужно, это непостоянные структуры в памяти, то рассмотрите вместо этого возможность использования QMap<QString, QVariant>.

     settings = new QSettings(settingsPath+"settings.ini",QSettings::IniFormat,this);
     loadSettings();

     
}



void Widget::loadSettings(){
    if (settings->value("proxy/useProxy").toBool()){
        //Настройка прокси
        webView->page()->networkAccessManager()->
                setProxy(QNetworkProxy(QNetworkProxy::HttpProxy,
                     settings->value("proxy/host").toString(),
                     settings->value("proxy/port").toInt(),
                     settings->value("proxy/user").toString(),
                     settings->value("proxy/password").toString()
                     )
                );

    }
    else{
        //Настройка прокси
         webView->page()->networkAccessManager()->setProxy(QNetworkProxy(QNetworkProxy::NoProxy));

    }

}



