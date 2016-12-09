# Qt_LockBox

##Описание проекта
Защищенное файловое хранилище. Приложение разработано в среде Qt с использованием крипто библиотеки botan. Файлы шифруются и расшифровываются при помощи алгоритма AES-128. 

##Подготовка к сборке проекта

1) Скачиваем последнюю версию Qt Creator. Download Qt Open Source: http://download.qt.io/official_releases/qt/5.7/5.7.0/qt-opensource-linux-x64-5.7.0.run

2) Скачиваем и собираем библиотеку botan: https://botan.randombit.net/#download

3) Скачиваем и собираем boost: http://www.boost.org/

##Сборка проекта

1) в файле .pro прописываем: LIBS += \-lboost_system -lboost_filesystem -lbotan-1.11\

2) в хэдере crypto.h прописываем в #include<> полные пути до хэдеров библиотеки botan 
 пример:  
 #include </usr/local/include/botan/botan.h>
 #include </usr/local/include/botan/pipe.h>
 #include </usr/local/include/botan/aes.h>
 #include </usr/local/include/botan/filters.h>

3) В конструкторе MainWindow прописываем путь до папки, которую хотите выбрать в качестве файлового хранилища (в ней сразу же создаете файл для хранения паролей "passwords")

  MainWindow::MainWindow(QWidget *parent) :
       QMainWindow(parent),
       ui(new Ui::MainWindow)
  {
      lockbox = path("Your_path/lockbox");
      .....
  }
  
4) Собираете проект :)
