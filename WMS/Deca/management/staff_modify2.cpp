#include "staff_modify2.h"
#include "ui_staff_modify2.h"
#include<QSqlQueryModel>
#include<QSqlQuery>
#include<QDebug>
#include<QSqlRecord>
#include<QMessageBox>

staff_modify2::staff_modify2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::staff_modify2)
{
    ui->setupUi(this);
    this->setWindowTitle("编辑员工信息");
    setAttribute(Qt::WA_DeleteOnClose);
     ui->pushButton->setShortcut(Qt::Key_Return);//将小键盘回车键与登录按钮绑定在一起
}

staff_modify2::~staff_modify2()
{
    delete ui;
}
void staff_modify2::displayImformation(QString staff_id)
{
    QSqlQuery query;
    query.exec("select *from staff_management where 员工编号 = "+staff_id+"");

    while(query.next())
    {
        ui->lineEdit->setText(query.value("员工编号").toString());
        ui->lineEdit_2->setText(query.value("姓名").toString());
        ui->lineEdit_3->setText(query.value("用户名").toString());
        ui->lineEdit_4->setText(query.value("邮箱").toString());
        ui->lineEdit_5->setText(query.value("电话").toString());
        ui->comboBox->setItemText(0,query.value("角色").toString());
    }

}
void staff_modify2::on_pushButton_2_clicked()
{
    this->close();
}

void staff_modify2::on_pushButton_clicked()
{
    QString str1,str2,str3,str4,str5,str6,str7;
    str1 = ui->lineEdit->text().trimmed();
    str2 = ui->lineEdit_2->text().trimmed();
    str3 = ui->lineEdit_3->text().trimmed();
    str4 = ui->lineEdit_4->text().trimmed();
    str5 = ui->lineEdit_5->text().trimmed();
    str6 = ui->comboBox->currentText().trimmed();
    str7 = ui->lineEdit_7->text().trimmed();
    QSqlQuery query;
    query.exec("update staff_management set 姓名 = '"+str2+"',用户名='"+str3+"',邮箱='"+str4+"',"
                     "电话='"+str5+"',角色='"+str6+"',备注='"+str7+"' where 员工编号 = '"+str1+"'");
    if (query.isActive())
    {
        QMessageBox::information(this, tr("信息"), tr("员工信息修改成功！"));
        this->close();
    }
    else
    {
        QMessageBox::warning(this, tr("警告"), tr("员工信息修改失败！"));

    }


}
