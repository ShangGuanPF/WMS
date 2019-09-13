#include "find_password.h"
#include "ui_find_password.h"
#include "login/find_result.h"
#include<QSqlQuery>
#include<QDebug>
#include<QSqlQueryModel>
#include<QMessageBox>
#include<QSqlRecord>
#include<QDesktopWidget>

find_password::find_password(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::find_password)
{
    ui->setupUi(this);
    this->setWindowTitle("密码查询");
     ui->pushButton->setShortcut(Qt::Key_Return);//将小键盘回车键与登录按钮绑定在一起
}

find_password::~find_password()
{
    delete ui;
}

void find_password::on_pushButton_clicked()
{
    QString staff_name = ui->lineEdit->text();
    QString true_name = ui->lineEdit_2->text();
    QSqlQuery query;
    query.exec("select *from staff_management where 用户名 = '"+staff_name+"'");
    if(!query.next())
    {
        QMessageBox::warning(this,tr("错误"),tr("请输入正确的登陆名"));
        ui->lineEdit->setText(NULL);
        ui->lineEdit_2->setText(NULL);
    }
    else
    {
        if(query.record().value("姓名").toString()!=true_name)
            {
            QMessageBox::warning(this,tr("错误"),tr("输入的真实姓名与登陆名不匹配"));
            ui->lineEdit->setText(NULL);
            ui->lineEdit_2->setText(NULL);
        }
        else
        {
            find_result *findresult = new find_result();
            findresult->setAttribute(Qt::WA_QuitOnClose,false);//主窗口关闭时同时关闭该窗口
            findresult->move((QApplication::desktop()->width() - findresult->width()) / 2,
                              (QApplication::desktop()->height() - findresult->height()) / 2);//桌面正中
            findresult->setWindowModality(Qt::ApplicationModal);//设置模态，禁止使用其他对话框
            findresult->show();
            QString password = query.record().value("密码").toString();

            connect(this,SIGNAL(sendpassword(QString,QString)),findresult,SLOT(displayPassword(QString,QString)));
            emit(sendpassword(password,staff_name));
            this->close();
        }
    }
}
