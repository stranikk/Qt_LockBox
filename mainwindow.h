#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "newuser.h"
#include <QMessageBox>
#include <boost/filesystem.hpp>
#include <addorread.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    NewUser* newUser;
    path lockbox;
    AddOrRead* AOR;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
   // void on_btn1_clicked();
    //void AddName(char*);
    //void on_Readbtn_clicked();

    void on_CreateNew_clicked();

    void on_LogIn_clicked();

    void on_Exit_clicked();

   // void on_checkBox_clicked();

signals:
    void UserChange(path);
    void LogPass(std::string, std::string);
    void Changed();

private:
    Ui::MainWindow *ui;

    std::string name;
    std::string pswd;
};

#endif // MAINWINDOW_H
