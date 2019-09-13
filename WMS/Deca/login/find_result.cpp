#include "find_result.h"
#include "ui_find_result.h"
#include "find_password.h"
#include "modify_password.h"
#include<QSqlQuery>
#include<QDebug>
#include<QSqlQueryModel>
#include<QMessageBox>
#include<QSqlRecord>
#include<QDesktopWidget>

find_result::find_result(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::find_result)
{
    ui->setupUi(this);
    this->setWindowTitle("查询结果");
     ui->pushButton->setShortcut(Qt::Key_Return);//将小键盘回车键与登录按钮绑定在一起
}

find_result::~find_result()
{
    delete ui;
}

void find_result::displayPassword(QString password,QString staff_name)
{
    ui->lineEdit->setText(password);
    ui->lineEdit_2->setText(staff_name);
}

void find_result::on_pushButton_2_clicked()
{
    this->close();

}

void find_result::on_pushButton_clicked()
{
    modify_password *modify_psw = new modify_password();
    modify_psw->setAttribute(Qt::WA_QuitOnClose,false);//主窗口关闭时同时关闭该窗口
    modify_psw->move((QApplication::desktop()->width() - modify_psw->width()) / 2,
                      (QApplication::desktop()->height() - modify_psw->height()) / 2);//桌面正中
    modify_psw->setWindowModality(Qt::ApplicationModal);//设置模态，禁止使用其他对话框
    modify_psw->show();
    QString read_name = ui->lineEdit_2->text().trimmed();
    QString read_password = ui->lineEdit->text().trimmed();
    connect(this,SIGNAL(sendMessage(QString,QString)),modify_psw,SLOT(displayImformation(QString,QString)));
    emit sendMessage(read_name,read_password);
    this->close();

}
