#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QStringListIterator>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // tạo signal cho lineEdit, khi enter thì sẽ tự động add item
    connect(ui->lineEdit, SIGNAL(returnPressed()),
            ui->addButton, SIGNAL(clicked()));
    fileOperator = new FileOperator(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::information(this,"About","This is my simple to do list application v.01");
}

void MainWindow::on_addButton_clicked()
{
    QString txt = ui->lineEdit->text().simplified();
    if(!txt.isEmpty())
        ui->listWidget->addItem(txt);
    ui->lineEdit->clear(); // after add task, line edit when clear all text
    ui->lineEdit->setFocus();
}

void MainWindow::on_removeButton_clicked()
{
    qDeleteAll(ui->listWidget->selectedItems());
}

void MainWindow::on_actionSave_triggered()
{
    fileOperator->save(createThingsToDoList());
}

void MainWindow::on_actionSave_as_triggered()
{
    fileOperator->saveAs(createThingsToDoList());
}

void MainWindow::on_actionOpen_triggered()
{
    QStringList thingsToDo = fileOperator->open();
    if(!thingsToDo.isEmpty()){
        ui->listWidget->clear();
        ui->listWidget->addItems(thingsToDo);
    }
}

QStringList MainWindow::createThingsToDoList()
{
    QStringList list;
    for(int i = 0; i < ui->listWidget->count(); i++)
        list << ui->listWidget->item(i)->text();
    return list;
}

void MainWindow::on_actionNew_triggered()
{
    while(ui->listWidget->count()>0)
    {
        delete ui->listWidget->takeItem(0);
    }
    fileOperator->newList();
}


