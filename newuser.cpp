#include "newuser.h"
#include "ui_newuser.h"

NewUser::NewUser(QWidget *parent, path p) :
    QDialog(parent),
    ui(new Ui::NewUser)
{
    lockbox = p;
    ui->setupUi(this);
}

NewUser::~NewUser()
{
    delete ui;
}

string NewUser::PswdToHash(string pass){
    QByteArray data(pass.c_str());
    QByteArray HashData =  QCryptographicHash::hash(data, QCryptographicHash::Sha224).toHex();
    return HashData.data();
}

void NewUser::on_pushButton_clicked()
{
    try{
       string name = ui->login->text().toStdString();
       string pswd = ui->password->text().toStdString();
       string pswd_repeat = ui->repeat->text().toStdString();
       if ((name == "")||(pswd == ""))
           throw "enter the name of user and password!";
       path a ("passwords");
       ifstream fin((lockbox/a).string().c_str()); // открыли файл для чтения

       bool find=false;
       while (!fin.eof()){ //пока не конец файла
              // fin.getline(buff, 50);
                string tmp_name;
                fin >> tmp_name;
               if (name == tmp_name)
                   find = true;
               else fin >> tmp_name;
               }
       fin.close();
        if (find)
            throw "This user already exist.";
        else{

            if (pswd!=pswd_repeat)
                throw "Passwords do not match.";
            pswd = PswdToHash(pswd);             //??
            ofstream fout((lockbox/a).string().c_str(), ios::app); //открыли файл для записи
            fout <<  name + " " + pswd + "\n" ;
            fout.close(); // закрываем файл
            path FileName (name);
            QDir().mkdir((lockbox/FileName.filename()).string().c_str());
            ui->login->clear();
            ui->password->clear();
            ui->repeat->clear();
            this->close();
        }
      }

      catch(char const*  message){
         QMessageBox::warning(this,"Enter correctly!", message);
      }
}

void NewUser::on_pushButton_2_clicked()
{
    ui->login->clear();
    ui->password->clear();
    ui->repeat->clear();
    this->close();
}
