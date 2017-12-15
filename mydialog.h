//SETTINGS DIALOG
#ifndef MYDIALOG_H
#define MYDIALOG_H
#include <QtWidgets>
#include <QSettings>
#include <QRegExpValidator>//для регулярных выражений
#include <QRegExp>

#include "mycheckbox.h"
class MyDialog: public QDialog
{
    Q_OBJECT
public:
    MyDialog(QSettings *mysettings,QWidget *parent);

private:
    //QCheckBox   *useProxyBox;
    MyCheckBox  *useProxyBox;
    QLineEdit   *hostEdit;
    QLineEdit   *portEdit;
    QLineEdit   *userEdit;
    QLineEdit   *passEdit;

    QPushButton *okButton;
    QPushButton *cancelButton;
    QPushButton *defaultButton;

    QSettings   *settings;

    QGridLayout *lay;

private slots:
    void setEnableLinesEdit();
    void okClicked(bool);
    void defaultClicked(bool);
    void useCheckBoxChanged(int);
    void on_hostEdit_textChanged(QString);
    void on_portEdit_textChanged(QString);
signals:
    void proxyChanged();
};


#endif // QDIALOG_H
