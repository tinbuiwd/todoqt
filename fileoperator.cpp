#include "fileoperator.h"
#include <QDebug>
#include <QFileDialog>
#include <QDir>
#include <QFileInfo>
#include <QFile>
#include <QMessageBox>

FileOperator::FileOperator(QWidget *parent) :
    QWidget(parent)
{
}

void FileOperator::save(QStringList thingsToDo)
{
    if(fileName.isEmpty())
        saveAs(thingsToDo);
    else
        performSaveOperation(fileName, thingsToDo);
}

void FileOperator::saveAs(QStringList thingsToDo)
{
    QString path = QDir::homePath();
    if(fileName != ""){
        QFileInfo info1(fileName);
        path = info1.absolutePath();
    }
    QString fn = QFileDialog::getSaveFileName(
                this,
                "Save as...",
                path,
                "ToDoList-file (*.tdolst);;Text files (*.txt);;All files (*)"
                );
    if(!fn.isEmpty()){
        QFileInfo info2(fn);
        QString ext = info2.suffix();
        if(ext != "tdolst" && ext != "txt")
            fn += ".tdolst";
        performSaveOperation(fn, thingsToDo);
    }
}


void FileOperator::performSaveOperation(QString fn, QStringList list)
{
    QFile file(fn);
    bool success = false;
    if (file.open(QFile::WriteOnly | QFile::Truncate | QFile::Text)) {
        QTextStream out(&file);
        for(int i = 0; i < list.count(); i++)
            out << list.at(i) << endl;
        if(file.error() == 0)
            success = true;
    }
    if(success)
        fileName = fn;
    else{
        QMessageBox mb;
        mb.setIcon(QMessageBox::Critical);
        mb.setText("Unable to save.");
        mb.setInformativeText("Try to do something smart.");
        mb.exec();
    }
}

QStringList FileOperator::open()
{
    QString path = QDir::homePath();
    if(fileName != ""){
        QFileInfo info(fileName);
        path = info.absolutePath();
    }
    QString fn = QFileDialog::getOpenFileName(
                this,
                "Open File...",
                path,
                "ToDoList (*.tdolst);;Text file (*.txt);;all file (*)"
                );
    QStringList thingsToDo;
    if(!fn.isEmpty())
        thingsToDo = performLoadOperation(fn);
    return thingsToDo;
}

void FileOperator::newList()
{
    fileName = "";
}

QStringList FileOperator::performLoadOperation(QString fn)
{
    QStringList thingsToDo;
    QFile file(fn);
    bool success = false;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in(&file);
        while (!in.atEnd())
            thingsToDo << in.readLine();
        if(file.error() == 0)
            success = true;
    }
    if(success)
        fileName = fn;
    else{
        QMessageBox mb;
        mb.setIcon(QMessageBox::Critical);
        mb.setText("Failed to open.");
        mb.setInformativeText("Try to do something smart.");
        mb.exec();
    }
    return thingsToDo;
}
