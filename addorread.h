#ifndef ADDORREAD_H
#define ADDORREAD_H

#include <crypt.h>
#include <QDialog>
#include <QString>
#include <fstream>
#include <QDir>
#include <QMessageBox>
#include <QCryptographicHash>
#include <string>
#include <boost/filesystem.hpp>
#include <QFileDialog>
#include <iostream>
#include "crypto.h"

using namespace std;
using namespace boost::filesystem;
namespace Ui {
class AddOrRead;
}

class AddOrRead : public QDialog
{
    Q_OBJECT

public:
    explicit AddOrRead(QWidget *parent = 0,path p = path(QDir::currentPath().toStdString()));
    QString logPasToKey(QString,bool);
    ~AddOrRead();


private slots:
    void setName(path);

    void setLogPass(string, string);

    void ShowFiles();

    void on_AddNew_clicked();

    void on_GetFile_clicked();

    void on_ReadFile_clicked();

    void on_ChangeUser_clicked();

    void on_Exit_clicked();

    void on_DeleteFile_clicked();

signals:
    void MainWin();

private:
    Ui::AddOrRead *ui;
    path lockbox;
    path name;
    string log, pswd;
    Crypto crpt;
};

#endif // ADDORREAD_H
