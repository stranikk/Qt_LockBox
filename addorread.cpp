#include "addorread.h"
#include "ui_addorread.h"
#include <QTextStream>

AddOrRead::AddOrRead(QWidget *parent, path p) :
    QDialog(parent),
    ui(new Ui::AddOrRead)
{
    lockbox = p;
    ui->setupUi(this);
}

AddOrRead::~AddOrRead()
{
    delete ui;
}

void AddOrRead::setLogPass(string l, string p){
    log = l;
    pswd = p;
}

void AddOrRead::setName(path p) {
    name = p;
}

QString AddOrRead::logPasToKey(QString logpas , bool mode)
{
    
    QByteArray ba=log.toUtf8();
    logpas=QCryptographicHash::hash(ba,QCryptographicHash::Sha256).toHex();
    logpas=log.mid(0,16);
    if (mode=="true"){
    for (int i{log.size()};i < 16;++i){
       log +="e";
       log.replace(QRegularExpression("[g-zG-Z]"), "f");
    }
    else{
       for (int i{log.size()};i < 16;++i){
       log +="c";
       log.replace(QRegularExpression("[g-zG-Z]"), "b");
    }
    return logpas;
}

void AddOrRead::ShowFiles(){
    ui->listWidget_2->clear();
    using rdi = recursive_directory_iterator;
    rdi end;

    for (rdi it(lockbox/name); it!=end; ++it)
        if( is_regular_file(it->path()) )
            ui->listWidget_2->addItem(QString::fromStdString(it->path().filename().string()));
}

void AddOrRead::on_AddNew_clicked()
{
   try{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Add file"), "../../", tr("Text files (*.txt);;All files (*)"));
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    std::vector<std::string> lines; //считываем из файла строки в вектор
    while (!file.atEnd()) {
           QByteArray line = file.readLine();
           lines.push_back((string)line.data());//??
    }

    path NamePath (file.fileName().toStdString());
    bool done = file.rename(fileName.toStdString().c_str(),  (lockbox/name/NamePath.filename()).string().c_str());
    if (!done){
        lines.clear();
        file.close();
        throw "Can`t add file.";
    }
    file.close();

    QString Log(log.c_str());
    QString Pswd(pswd.c_str());
    std::string shifr;
    ofstream fout((lockbox/name/NamePath.filename()).string().c_str()); //открыли файл для записи
    for (unsigned int i = 0; i<lines.size(); i++){ //записываем в открытый файл зашифрованные строки из вектора
        shifr = crpt.MyShifr(lines[i],logPasToKey(Log,true).toStdString(),logPasToKey(Pswd,false).toStdString(),true);
        fout << shifr << "\n";
    }
    fout.close(); // закрываем файл
    ShowFiles(); //выводим обновленный список файлов в ListWidget_2
   }
   catch(char const* message){
       QMessageBox::warning(this,"Adding file", message);
   }
}

void AddOrRead::on_ReadFile_clicked()
{
    try{
        ui->listWidget->clear();
        if (ui->listWidget_2->selectedItems().empty())
            throw "you should choose the file you want to read";

        auto SelectedPath = ui->listWidget_2->currentItem();

        QString filePath = QString::fromStdString((lockbox/name).string()+'/'+SelectedPath->text().toStdString());
        QFile file(filePath);
        if (!exists(path(filePath.toStdString()))){
            delete SelectedPath;
            throw "this file was deleted :c";
        }

        QString Log(log.c_str());
        QString Pswd(pswd.c_str());
        file.open(QIODevice::ReadOnly);
        while (!file.atEnd()) {
               QByteArray line = file.readLine();
               string deshifr = crpt.MyShifr((string)line.data(),logToKey(Log).toStdString(),logToKey(Pswd).toStdString(),false);
               QString a(deshifr.c_str());
               ui->listWidget->addItem(a);
        }
        file.close();
       }
    catch(char const*  message){
        QMessageBox::warning(this,"Reading file", message);
    }
}

void AddOrRead::on_GetFile_clicked()
{
    try{
        ui->listWidget->clear();
        if (ui->listWidget_2->selectedItems().empty())
            throw "you should choose the file";

        auto SelectedPath = ui->listWidget_2->currentItem();

        QString filePath = QString::fromStdString((lockbox/name).string()+'/'+SelectedPath->text().toStdString());
        QFile file(filePath);
        if (!exists(path(filePath.toStdString()))){
            delete SelectedPath;
            throw "this file was deleted :c";
        }

        QString Log(log.c_str());
        QString Pswd(pswd.c_str());

        QString OutPath=QFileDialog::getSaveFileName(this, tr("Save File"), "../untitled.txt", tr("Text files (*.txt);;All files (*.*)"));

        QFile OutFile(OutPath);
        bool ok = OutFile.open(QIODevice::WriteOnly);
        if (!ok)
            throw "File error";

        QTextStream out(&OutFile);
        file.open(QIODevice::ReadOnly);
        while (!file.atEnd()) {
               QByteArray line = file.readLine();
               string deshifr = crpt.MyShifr((string)line.data(),logPasToKey(Log,true).toStdString(),logPasToKey(Pswd,false).toStdString(),false);
               QString a(deshifr.c_str());
               out << a;
        }
        file.remove();
        delete SelectedPath;
        file.close();
        OutFile.close();
    }

    catch(char const*  message){
        QMessageBox::warning(this,"Getting file from box", message);
    }
}

void AddOrRead::on_ChangeUser_clicked()
{
    emit MainWin();
    ui->listWidget->clear();
    this->close();
}

void AddOrRead::on_Exit_clicked()
{
    this->close();
}

void AddOrRead::on_DeleteFile_clicked()
{
    try{
        ui->listWidget->clear();
        if (ui->listWidget_2->selectedItems().empty())
            throw "you should select the file you want to remove";

        auto SelectedPath = ui->listWidget_2->currentItem();

        QString filePath = QString::fromStdString((lockbox/name).string()+'/'+SelectedPath->text().toStdString());
        QFile file(filePath);
        if (!exists(path(filePath.toStdString()))){

            delete SelectedPath;
            file.close();
            throw "This file has already been removed!";
        }
        file.remove();
        delete SelectedPath;
    }
    catch(char const*  message){
        QMessageBox::warning(this,"Removing file", message);
    }

}
