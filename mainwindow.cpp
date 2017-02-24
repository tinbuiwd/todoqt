#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::information(this,"About","This is my simple to do list application v.01");
}

void MainWindow::on_btnClearAll_clicked()
{
    ui->listWidget->clear(); //clear all task list.
}

void MainWindow::on_btnDelete_clicked()
{
    QList<QListWidgetItem*> selectedItems = ui->listWidget->selectedItems();
    int length = selectedItems.length();
    for(int i=0; i<length; i++){
         QListWidgetItem* item = selectedItems.at(i);
         delete item;
    }
}

void MainWindow::on_btbAddNew_clicked()
{
    // Add a new task
    QString text = ui->lineEdit->text();
    if(!text.isEmpty()){
        ui->listWidget->addItem(text);
        ui->lineEdit->clear();
    }
}
