#include "calendar.h"
#include "ui_calendar.h"
#include <QtDebug>
#include <QtSql>


calendar::calendar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::calendar)
{
    ui->setupUi(this);
}

calendar::~calendar()
{
    delete ui;
}

void calendar::on_cancelButton_clicked()
{
    //Close window if task creation was cancelled
    this->close();
}

void calendar::on_createButton_clicked()
{
    //Create new task to the database
    //Parse string from the selected date in the calendar
    QString dateString = ui->calendarWidget->selectedDate().toString("dd.MM.yyyy");

    //Open db connection
    QString db_name = "todo_db";
    QSqlDatabase db = QSqlDatabase::database(QSqlDatabase::defaultConnection);
    db.setDatabaseName(db_name);
    db.open();

    //Create prepared query to avoid malicious input to the db
    QSqlQuery query;
    query.prepare("insert into task (description, status, deadline) values (:description, :status, :deadline)");
    query.bindValue(":description", ui->taskDescripitionTextEdit->text());
    query.bindValue(":status", "Not done");
    query.bindValue(":deadline", dateString);
    query.exec();

    db.close();

    this->close();
}

void calendar::closeEvent(QCloseEvent *event)
{
    //Let taskwindow know weve closed the calendar
    emit windowClosed();
}
