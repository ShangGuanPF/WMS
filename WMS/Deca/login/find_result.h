#ifndef FIND_RESULT_H
#define FIND_RESULT_H

#include <QWidget>

namespace Ui {
class find_result;
}

class find_result : public QWidget
{
    Q_OBJECT

public:
    explicit find_result(QWidget *parent = 0);
    ~find_result();
private slots:
    void displayPassword(QString password,QString staff_name);
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::find_result *ui;
signals:
    void sendMessage(QString,QString);
};

#endif // FIND_RESULT_H
