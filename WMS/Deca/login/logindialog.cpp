#include "logindialog.h"
#include "ui_logindialog.h"
#include "wms/connect_database.h"
#include "management/add_staff.h"
#include "login/find_password.h"
#include<QSqlQuery>
#include<QDebug>
#include<QSqlQueryModel>
#include<QMessageBox>
#include<QSqlRecord>
#include<QDesktopWidget>

loginDialog::loginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("用户登陆");
    ui->lineEdit->setPlaceholderText("Username");//设置当鼠标点击文本时设置内容消失
    ui->lineEdit_2->setPlaceholderText("Password");
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
}

loginDialog::~loginDialog()
{
    delete ui;
}

void loginDialog::on_pushButton_clicked()
{

    QString user_account;
    QString user_pwd;

    user_account = ui->lineEdit->text();
    user_pwd  = ui->lineEdit_2->text();

    QSqlQuery query;

    if (!ConnectDatabase::openDatabase())
    {
        QMessageBox::warning(this, tr("错误"), tr("打开数据库失败!"));
        return ;
    }
    else
    {
            query.exec("select * from staff_management where 用户名='"+user_account+"'");
            if(!query.next())
            {
                QMessageBox::warning(this, tr("错误"), tr("请输入正确的登陆名!"));
                ui->lineEdit->clear();
                ui->lineEdit_2->clear();
            }
            else
            {
                QString staff_match = query.record().value("密码").toString();
                if(staff_match==user_pwd)
                {
                    QDialog::accept();
                }
                else
                {
                    QMessageBox::warning(this, tr("错误"), tr("请输入正确的密码再登陆!"));
                   ui->lineEdit_2->clear();
                   // ui->lineEdit_2->clear();
                }
            }

     }
}

void loginDialog::on_toolButton_clicked()
{
    add_staff *add_stf = new add_staff();
    add_stf->setAttribute(Qt::WA_QuitOnClose,false);//主窗口关闭时同时关闭该窗口
    add_stf->move((QApplication::desktop()->width() - add_stf->width()) / 2,
                      (QApplication::desktop()->height() - add_stf->height()) / 2);//桌面正中
    add_stf->setWindowModality(Qt::ApplicationModal);//设置模态，禁止使用其他对话框
    add_stf->show();
}

void loginDialog::on_toolButton_3_clicked()
{
    find_password *findpassword = new find_password();
    findpassword->setAttribute(Qt::WA_QuitOnClose,false);//主窗口关闭时同时关闭该窗口
    findpassword->move((QApplication::desktop()->width() - findpassword->width()) / 2,
                      (QApplication::desktop()->height() - findpassword->height()) / 2);//桌面正中
    findpassword->setWindowModality(Qt::ApplicationModal);//设置模态，禁止使用其他对话框
    findpassword->show();
}
