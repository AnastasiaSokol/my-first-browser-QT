#ifndef HISTORDIALOG_H
#define HISTORDIALOG_H
#include <QtWidgets>
#include <QTableWidget>
#include <QWebHistory>
#include "mybutton.h"

class HistorDialog: public QDialog{
    Q_OBJECT
public:
    HistorDialog(QString filepath, QWidget *parent);

private:
    QTableWidget    *table;
    MyButton        *clearhistorybutton;
    MyButton        *deleteSelectedButton;
    QGridLayout     *lay;
    QString         child;
    QWebHistory     *myhistory;//история объекта WebView
    QString         myfilepath;
    QString         linehistory;

    QComboBox       *BoxPeriod;//Выпадающий список с выбором периода просмотра истории
    QStringList     periodsList; // список периодов

    QString         url;
    QString         title;
    QString         time;
    QString         date;

    QStringList     li; // список заголовков

    QStringList     urlList; // список URL
    QStringList     titleList; // список title
    QStringList     timeList; // список time
    QStringList     dateList; // список date

    int             row;
    int             col;
private slots:
    void HistorCellClicked(int row, int col);
    void ClearHistorClicked();
    void DeleteSelectedCell();
    void ShowForPeriod(int index);
signals:
    void gotUrl(QString);
};
#endif // HISTORDIALOG_H
