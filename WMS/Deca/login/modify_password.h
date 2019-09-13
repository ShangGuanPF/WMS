#ifndef MODIFY_PASSWORD_H
#define MODIFY_PASSWORD_H

#include <QWidget>

namespace Ui {
class modify_password;
}

class modify_password : public QWidget
{
    Q_OBJECT

public:
    explicit modify_password(QWidget *parent = 0);
    ~modify_password();

private slots:
    void on_pushButton_2_clicked();
    void displayImformation(QString,QString);

    void on_pushButton_clicked();

private:
    Ui::modify_password *ui;
};

#endif // MODIFY_PASSWORD_H
