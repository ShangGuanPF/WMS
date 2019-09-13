#ifndef FIND_PASSWORD_H
#define FIND_PASSWORD_H

#include <QWidget>

namespace Ui {
class find_password;
}

class find_password : public QWidget
{
    Q_OBJECT

public:
    explicit find_password(QWidget *parent = 0);
    ~find_password();

private slots:
    void on_pushButton_clicked();
signals:
    void sendpassword(QString,QString);

private:
    Ui::find_password *ui;
};

#endif // FIND_PASSWORD_H
