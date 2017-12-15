#ifndef TABDIALOG_H
#define TABDIALOG_H

#include <QtWidgets>
#include <QTableWidget>
#include "mybutton.h"

class TabDialog: public QDialog{
    Q_OBJECT
public:
    TabDialog(QString filepath, QWidget *parent);

private:
    QTableWidget    *table;
    MyButton        *clearbutton;
    MyButton        *deleteSelectedButton;
    MyButton        *goButton;
    QGridLayout     *lay;
    QString         path;
    QString         lineTab;
    QString         url;
    QString         title;
    QStringList     li; // список заголовков таблицы
    QStringList     urlList; // список URL
    QStringList     titleList; // список title
    int             row;
    int             col;
private slots:
    void TabCellClicked(int row, int col);
    void ClearTabsClicked();
    void DeleteSelectedCell();
    void GoClicked();
signals:
    void gotoUrl(QString);
};


#endif // TABDIALOG_H
