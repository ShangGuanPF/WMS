#include "modify_password.h"
#include "ui_modify_password.h"
#include<QSqlQuery>
#include<QDebug>
#include<QSqlQueryModel>
#include<QMessageBox>
#include<QSqlRecord>
#include<QDesktopWidget>

modify_password::modify_password(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::modify_password)
{
    ui->setupUi(this);
    this->setWindowTitle("密码修改");
    ui->pushButton->setShortcut(Qt::Key_Return);//将小键盘回车键与登录按钮绑定在一起
}

modify_password::~modify_password()
{
    delete ui;
}

void modify_password::on_pushButton_2_clicked()
{
    this->close();
}

void modify_password::displayImformation(QString name,QString password)
{
  ui->lineEdit->setText(name);
  ui->lineEdit_2->setText(password);

}

void modify_password::on_pushButton_clicked()
{
    QString staff_name = ui->lineEdit->text().trimmed();
    QString set_password = ui->lineEdit_3->text().trimmed();
    QString affirm_password = ui->lineEdit_4->text().trimmed();
    if(set_password == affirm_password)
    {
        QSqlQuery query;
        query.exec("update staff_management set 密码='"+set_password+"',确认密码='"+set_password+"'"
                                                                       "where 用户名='"+staff_name+"'");
        if (query.isActive())
        {
            QMessageBox::information(this, tr("信息"), tr("密码修改成功！"));
            this->close();
        }
        else
        {
            QMessageBox::warning(this, tr("警告"), tr("密码修改失败！"));

        }
    }
    else
    {
        QMessageBox::warning(this, tr("错误"), tr("密码前后不一致!"));
        ui->lineEdit_3->setText(NULL);
        ui->lineEdit_4->setText(NULL);
    }
}
