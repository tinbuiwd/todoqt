#include "taskwindow.h"
#include "ui_taskwindow.h"
#include "calendar.h"
#include <QTextStream>
#include <QtDebug>
#include <QtSql>
#include <QMessageBox>
#include <QVector>

TaskWindow::TaskWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TaskWindow)
{
    ui->setupUi(this);

    //Initially show all tasks
    showDone = true;
    showNotDone = true;

    //Fetch first data
    refreshTable();
}

TaskWindow::~TaskWindow()
{
    delete ui;
}
void TaskWindow::on_pushButton_clicked()
{
    //Open calendar for creating new task
       acalendar = new calendar();
       connect(acalendar, &calendar::windowClosed, this, &TaskWindow::returnToTaskWindow);
       acalendar->show();

    //Disable main window so that user doesn't edit it when making new task
    this->setEnabled(false);
}

QString TaskWindow::createFilter(){
    //Create filter to pick the tasks to show in qtableview
    QString filter = "";
    if(showDone){
        filter.append("status='Done'");
    }
    if(showDone && showNotDone)
        filter.append(" or ");
    if(showNotDone)
        filter.append("status='Not done'");
    //Empty filter means nothing will be selected
    if(filter.length() == 0){
        filter = "status NOT 'Not done' and status NOT 'Done'";
    }
    return filter;
}

void TaskWindow::refreshTable(){
    //refresh the contents of the qtableview

    //Create model and fetch data
    model = new QSqlTableModel(this);
    model->setTable("task");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    QString filter = createFilter();
    model->setFilter(filter);
    model->select();

    //Set headers
    model->setHeaderData(0, Qt::Horizontal, tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, tr("Description"));
    model->setHeaderData(2, Qt::Horizontal, tr("Status"));
    model->setHeaderData(3, Qt::Horizontal, tr("Deadline"));

    //Set up the qtableview
    QTableView *view = ui->tableView;
    view->setModel(model);
    //Add combobox delegate for done/not done.
    view->setItemDelegateForColumn(2, &aComboBoxDelegate);
    view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //Dont need to show the id to user
    view->hideColumn(0);

    //Connect to datachanged signal from qtableview so that revert- and save buttons will be enabled at correct time
    connect(ui->tableView->model(), SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)), this, SLOT(onDataChanged()));

    //Disable save/revert buttons because data is now up-to-date
    ui->revertChangesButton->setEnabled(false);
    ui->saveChangesButton->setEnabled(false);
}

void TaskWindow::onDataChanged()
{
    //Enable save and revert buttons when the data changes
    ui->revertChangesButton->setEnabled(true);
    ui->saveChangesButton->setEnabled(true);
}


void TaskWindow::returnToTaskWindow(){
    //This is called when creation of new task ends

    //refresh table to fetch possible new tasks
    refreshTable();
    //return main window to be editable
    this->setEnabled(true);
}

QVector<int> TaskWindow::checkDates(){
    //Check the dates user has input to make sure they contain no invalid values

    int row = model->rowCount();
    QVector<int> invalidDateVector;
    //iterate through qtableview's deadline column
    for (int i = 0; i < row ; ++i)
    {
        //get content of cell and try to parse it into qdatetime
        QVariant content = model->data(model->index(i, 3), Qt::DisplayRole);
        QString currentCellDate(content.toString());
        QDateTime parsedDate = QDateTime::fromString(currentCellDate, "dd.MM.yyyy");
        if(!parsedDate.isValid()){
            invalidDateVector.push_back(i + 1);
        }

    }
    return invalidDateVector;
}

int TaskWindow::showMsgBox(QString text, QString informativeText){
    //Show simple messagebox to tell user if things go right or wrong
    QMessageBox msgBox;
    msgBox.setText(text);
    msgBox.setInformativeText(informativeText);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    return msgBox.exec();
}

void TaskWindow::on_saveChangesButton_clicked()
{
    //check for invalid dates
    QVector<int>invalidDateVector = checkDates();
    if(invalidDateVector.length() > 0){
        //If invalid dates exist, parse them into a comma separated string
        QString invalidDateString = "";
        for(int i = 0; i < invalidDateVector.length(); i++){
            invalidDateString.append(QString::number(invalidDateVector.at(i)));
            if(i < invalidDateVector.length() - 1)
                invalidDateString.append(", ");
        }

        //display message box to user and return without saving changes
        QString text = "Error!";
        QString informativeText = "Invalid dates on following lines:\n\n" + invalidDateString + "\n\nNo changes were saved. Please fix the lines and try again.";
        showMsgBox(text , informativeText);
        return;
    }

    //Attempt to store changes
    if(model->submitAll()){
        //If succesful, let user know
        model->database().commit();
        QString text = "Success!";
        QString informativeText = "Changes saved";
        showMsgBox(text, informativeText);
        refreshTable();
    }
    else{
        //If not succesful, let user know about it too
        model->database().rollback();
        showMsgBox("Error!", "Committing changes to the database failed");
    }
}

void TaskWindow::on_revertChangesButton_clicked()
{
    //Revert changes and roll back
    model->revertAll();
    model->database().rollback();
    //qDebug()<< "da revert thanh cong";
    refreshTable();
}

//Slots for the checkboxes used for filtering done and not done tasks
void TaskWindow::on_showNotDoneCheckBox_stateChanged(int task)
{
    if(task)
    {
        showNotDone = true;
        //qDebug()<< "check thanh cong";
    }
    else
    {
        showNotDone = false;
        //qDebug()<< "check khong thanh cong";
    }
    refreshTable();
}

void TaskWindow::on_showDoneCheckBox_stateChanged(int task)
{
    //QTextStream(stdout) << task << endl; //check value off task
    if(task)
    {
        showDone = true;
    }
    else
    {
        showDone = false;
        //qDebug()<< "check khong thanh cong";

    }
    refreshTable();
}

