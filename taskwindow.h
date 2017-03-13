#ifndef TASKWINDOW_H
#define TASKWINDOW_H

#include <QWidget>
#include <QtSql>
#include "calendar.h"
#include "comboboxdelegate.h"

namespace Ui {
class TaskWindow;
}

class TaskWindow : public QWidget
{
    Q_OBJECT

public:
    explicit TaskWindow(QWidget *parent = 0);
    ~TaskWindow();

private slots:
    void on_pushButton_clicked();
    void on_saveChangesButton_clicked();
    void on_revertChangesButton_clicked();
    void on_showNotDoneCheckBox_stateChanged(int agr1);
    void on_showDoneCheckBox_stateChanged(int arg1);
    void onDataChanged();

public slots:
    void returnToTaskWindow();

private:
    Ui::TaskWindow *ui;
    calendar *acalendar;
    ComboBoxDelegate aComboBoxDelegate;
    QSqlTableModel *model;
    bool showDone;
    bool showNotDone;
    void refreshTable();
    QString createFilter();
    QVector<int> checkDates();
    int showMsgBox(QString text, QString informativeText);


};

#endif // TASKWINDOW_H
