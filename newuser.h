#ifndef NEWUSER_H
#define NEWUSER_H

#include <QDialog>
#include <fstream>
#include <QDir>
#include <QMessageBox>
#include <QCryptographicHash>
#include <string>
#include <boost/filesystem.hpp>

using namespace std;
using namespace boost::filesystem;

namespace Ui {
class NewUser;
}

class NewUser : public QDialog
{
    Q_OBJECT

public:
    explicit NewUser(QWidget *parent = 0, path p = path(QDir::currentPath().toStdString()));
    ~NewUser();
    string PswdToHash(string);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::NewUser *ui;
    path lockbox;
};

#endif // NEWUSER_H
