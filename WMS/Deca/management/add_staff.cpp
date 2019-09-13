#include "add_staff.h"
#include "ui_add_staff.h"
#include<QSqlQuery>
#include<QMessageBox>


add_staff::add_staff(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::add_staff)
{
    ui->setupUi(this);
    this->setWindowTitle("新增员工信息");
    setAttribute(Qt::WA_DeleteOnClose);
     ui->pushButton_2->setShortcut(Qt::Key_Return);//将小键盘回车键与登录按钮绑定在一起
}

add_staff::~add_staff()
{
    delete ui;
}

void add_staff::on_pushButton_3_clicked()
{
    this->close();
}

void add_staff::on_pushButton_clicked()
{
    ui->lineEdit_7->setText(NULL);
    ui->lineEdit_2->setText(NULL);
    ui->lineEdit_3->setText(NULL);
    ui->lineEdit_4->setText(NULL);
    ui->lineEdit_5->setText(NULL);
    ui->lineEdit_6->setText(NULL);
    ui->lineEdit_8->setText(NULL);
}

void add_staff::on_pushButton_2_clicked()
{
    QString str2,str3,str4,str5,str6,str7,str8,str9;
    str2 = ui->lineEdit_2->text().trimmed();
    str3 = ui->lineEdit_3->text().trimmed();
    str4 = ui->lineEdit_4->text().trimmed();
    str5 = ui->lineEdit_5->text().trimmed();
    str6 = ui->lineEdit_6->text().trimmed();
    str7 = ui->lineEdit_7->text().trimmed();
    str8 = ui->lineEdit_8->text().trimmed();
    str9 = ui->comboBox->currentText().trimmed();
        if(str2==NULL||str3==NULL||str4==NULL||str5==NULL||str6==NULL||str7==NULL)
        {
            QMessageBox::warning(this, tr("警告"), tr("请将信息填写完整！"));
        }
        else if(str3!=str4)
            {
            QMessageBox::warning(this, tr("警告"), tr("前后密码填写不一致！"));
            ui->lineEdit_3->setText(NULL);
            ui->lineEdit_4->setText(NULL);
        }
        else
        {
            QSqlQuery query;
            query.prepare("insert into staff_management(姓名,密码,确认密码,用户名,邮箱,电话,角色,备注)"
                       " values(:two,:three,:four,:five,:six,:seven,:eight,:nine)");
            query.bindValue(":two",str2);
            query.bindValue(":three",str3);
            query.bindValue(":four",str4);
            query.bindValue(":five",str5);
            query.bindValue(":six",str6);
            query.bindValue(":seven",str7);
            query.bindValue(":eight",str9);
            query.bindValue(":nine",str8);
            query.exec();
            if(query.isActive())
                {
                query.numRowsAffected();
                QMessageBox::information(this, tr("信息"), tr("信息注册成功！"));
                this->close();
                }
            else
                QMessageBox::warning(this, tr("警告"), tr("注册失败！"));
        }





}
