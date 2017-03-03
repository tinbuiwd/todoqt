#ifndef calendar_H
#define calendar_H

#include <QWidget>

namespace Ui {
class calendar;
}

class calendar : public QWidget
{
    Q_OBJECT

public:
    explicit calendar(QWidget *parent = 0);
    ~calendar();

protected:
    void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;

private slots:
    void on_cancelButton_clicked();
    void on_createButton_clicked();


signals:
    void windowClosed();

private:
    Ui::calendar *ui;


};

#endif // calendar_H
