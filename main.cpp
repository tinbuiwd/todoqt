#include "taskwindow.h"
#include <QApplication>
#include <QtSql>
#include <QMessageBox>

bool init_db(){
    //initialize database and create the task table
    QString db_name = "todo_db";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(db_name);
    if(!db.open()){
        return false;
    }
    QSqlQuery query;

//    QSqlDatabase db;
//        db = QSqlDatabase::addDatabase("QMYSQL");

//        db.setHostName("192.168.119.1");
//        db.setPort(3306);
//        db.setDatabaseName("todo");
//        db.setUserName("");
//        db.setPassword("");
//        qDebug()<<db.open();

    bool createTableSuccessful = query.exec("create table if not exists task " \
              "(id integer primary key, " \
              "description varchar(200), " \
              "status varchar (10), " \
              "deadline varchar(30))");
    db.close();
    if(!createTableSuccessful){
       return false;
    }

   return true;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Try to initialize db
    if(!init_db()){
        //Show messagebox with error if initialization failed
        QMessageBox msgBox;
        msgBox.setText("Error!");
        msgBox.setInformativeText("Initial database setup failed!");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.show();
        return msgBox.exec();
    }

    //Show primary task window
    TaskWindow w;
    w.show();

    return a.exec();
}
