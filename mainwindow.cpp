#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    lockbox = path("/home/nikolay/QtProjects/FirstProject/lockbox");
    newUser = new NewUser(this, lockbox.string());
    AOR = new AddOrRead(0, lockbox);

    ui->setupUi(this);

    connect(this, SIGNAL(UserChange(path)), AOR, SLOT(setName(path)));
    connect(this, SIGNAL(LogPass(string, string)), AOR, SLOT(setLogPass(string, string)));
    connect(this, SIGNAL(Changed()), AOR, SLOT(ShowFiles()));
    connect(AOR, &AddOrRead::MainWin, this, &MainWindow::show);
}

MainWindow::~MainWindow()
{
    delete AOR;
    delete newUser;
    delete ui;
}

void MainWindow::on_CreateNew_clicked()
{
    newUser -> setModal(true);
    newUser -> show();
}

void MainWindow::on_LogIn_clicked()
{
       try{

        name = ui->nickName->text().toStdString();
        pswd = ui->Password->text().toStdString();
        string pass = newUser->PswdToHash(pswd);
        if ((name == "")||(pswd == ""))
            throw "enter the name of user and password!";
        ifstream fin(lockbox.string() +"/passwords"); // открыли файл для чтения

        bool find=false;
        while (!fin.eof()){ //пока не конец файла

            string tmp_name;
            fin >> tmp_name;
            if (name == tmp_name) {
               find = true;
               fin >> tmp_name;
               if (pass != tmp_name)
                   find = false;
            }
            else fin >> tmp_name;
        }
        fin.close();
        if (!find)
            throw "Uncorrect login or password.";

        path a(lockbox.string()+"/"+name);
        if (!exists(a))
            throw "Sorry! This user was deleted :(";

        AOR->show();
        emit UserChange(path(name));
        emit LogPass(name, pswd);
        emit Changed();
        ui->nickName->clear();
        ui->Password->clear();
        this->close();
    }

    catch(char const*  message){
        QMessageBox::warning(this,"Warning!", message);
    }
}

void MainWindow::on_Exit_clicked()
{
    this->close();
}
