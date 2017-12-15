//MAIN DIALOG OF OUR BRAUSER
#ifndef WIDGET_H//директивы процессора
#define WIDGET_H

#include <QWidget>//заменяет слово include... и запихивает сюда библиотеку QWidget код
//#include <QPushButton>
//#include <QtGui>//модуль QT содержит все ГЭ
#include <QtWebKitWidgets>
#include <QSettings>
#include <QTextStream>//Для сохранения в файл
#include <QFile>//файл
#include <QPixmap>//для загрузки картинки в labelscale
#include "mybutton.h"
#include "mymenu.h"
#include "mydialog.h"
#include "histordialog.h"
#include "tabdialog.h"

class Widget : public QWidget
{
    Q_OBJECT//macros  это кусок кода который подставляется не на этапе компиляции

public:
    Widget(QWidget *parent = 0);//конструктор
    ~Widget();//деструктор
    void goToUrlFromHistory(QString url);
    //методы которые в сексии слотс
    //чтобы Qt знала что можно с ним связывать сигналы-события
protected slots:
    void closeClicked();
    void settingsClicked();
    void historyClicked();
    void showTabsClicked();
    void saveHistory(QUrl);
private slots:
    void mySlot();
    void goURL();

    void goURLFromHistory(QString url);//загрузка страницы из истории браузера
    void goURLFromTabDialog(QString url);//загрузка страницы из диалога просмотра закладок

    void pageLinkClicked(QUrl);
    void pageTitleChanged(QString);
    void pageUrlChanged (QUrl url);

    void PrevButtonclicked();
    void NextButtonclicked ();
    void RefreshButtonclicked ();
    void StopButtonclicked ();
    void favoriteButtonClicked();

    void pageLoadStarted();
    void pageLoadFinished();
    void changePageScale(int value);
    void loadSettings();


private:
    //ссылка на диалог истории
    HistorDialog *historyD;
    TabDialog    *tabD;
    //кнопки управления
    /*
    QLabel      *label1;
    MyButton    *prevbutton1;
    MyButton    *nextbutton2;
    MyButton    *stopbutton3;
    MyButton    *refreshbutton4;
    MyButton    *gobutton5;
    */
    QLineEdit   *adresstr;
    //строка состояния
    QLabel      *labelCondition;
    //элементы для установки масштаба
    QHBoxLayout *layScale;
    QLabel      *labelScale;
    QSpinBox    *spinboxScale;
    QSlider     *sliderScale;
    //Меню
    QMenuBar    *menuBar;
    MyMenu      *mainMenu;
    QAction     *showOurTabsAction;
    QAction     *tabAction;
    QAction     *goAction;
    QAction     *backAction;
    QAction     *reloadAction;
    QAction     *settingsAction;
    QAction     *closeAction;
    QAction     *historyAction;
    //компоновщики
    QVBoxLayout *mainlay1;
    QVBoxLayout *innerlay1;
    QHBoxLayout *toolbarlay2;
    QHBoxLayout *StatusBarLay;
    //настройки
    QSettings   *settings;
    void openSettings();
    //страница отображения
     QWebView   *webView;
    //сохранение в файл
     QFile      *myfile;
     QTextStream *mytextstream;
     QString    filepathhistory;
     QString    filepathtab;
};

#endif // WIDGET_H
