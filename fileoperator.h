#ifndef FILEOPERATOR_H
#define FILEOPERATOR_H

#include <QWidget>
#include <QString>

class FileOperator : public QWidget
{
    Q_OBJECT
private:
    QString fileName;
    void performSaveOperation(QString fn, QStringList list);
    QStringList performLoadOperation(QString fn);

public:
    explicit FileOperator(QWidget *parent = 0);
    void save(QStringList thingsToDo);
    void saveAs(QStringList thingsToDo);
    QStringList open();
    void newList();

signals:

public slots:

};

#endif // FILEOPERATOR_H
