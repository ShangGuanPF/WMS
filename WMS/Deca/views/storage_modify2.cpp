#include "storage_modify2.h"
#include "ui_storage_modify2.h"
#include <QString>
#include <QSqlQuery>
#include <QMessageBox>
#include<QSqlQueryModel>
#include<QSqlRecord>
#include <cstdio>
storage_modify2::storage_modify2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::storage_modify2)
{
    ui->setupUi(this);

    this->setWindowTitle("订单修改");
    QFont ft;
    ft.setPointSize(18);
    ui->label->setFont(ft);
    //向combobox中添加元素
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("select 仓库名称 from stores_management");
    int rowNum = model->rowCount();
    for(int i = 0;i<rowNum;i++)
    {
        QString str = model->record(i).value(0).toString();
        ui->comboBox->addItem(str);
     }
    QSqlQueryModel *model1 = new QSqlQueryModel();
    model1->setQuery("select 员工名 from staff_management");
    int rowNum1 = model1->rowCount();
    for(int i = 0;i<rowNum1;i++)
    {
        QString str1 = model1->record(i).value(0).toString();
        ui->comboBox_2->addItem(str1);
     }
     ui->pushButton->setShortcut(Qt::Key_Return);//将小键盘回车键与登录按钮绑定在一起
}

void storage_modify2:: displayAllInformation(QString data)
{
    QString order_id=data;
    QSqlQuery query;
    order_id_global=data;
    query.exec("select * from storage_copy where 订单号='"+order_id+"'");
    if(query.next())
    {
        ui->lineEdit1->setText(query.value(0).toString());
        ui->lineEdit2->setText(query.value(1).toString());
        ui->lineEdit3->setText(query.value(2).toString());
        ui->lineEdit4->setText(query.value(3).toString());
        ui->lineEdit5->setText(query.value(4).toString());
        ui->comboBox->setItemText(0,query.value("仓库").toString());
        ui->comboBox_2->setItemText(0,query.value("管理员").toString());
        ui->lineEdit8->setText(query.value(7).toString());
    }
    else
        QMessageBox::warning(this, tr("警告"), tr("没有此订单的相关信息！"));
}


storage_modify2::~storage_modify2()
{
    delete ui;
}

void storage_modify2::on_pushButton_3_clicked()
{
    this->close();
}

void storage_modify2::on_pushButton_2_clicked()
{
    ui->lineEdit2->setText("");
    ui->lineEdit3->setText("");
    ui->lineEdit4->setText("");
    ui->lineEdit5->setText("");

}

void storage_modify2::on_pushButton_clicked()
{
    QString str1;
    QString str2;
    QString str3;
    QString str4;
    QString str5;
    QString str6;
    QString str7;
    QString str8;
    QSqlQuery query;
    str1=ui->lineEdit1->text();
    str2=ui->lineEdit2->text();
    str3=ui->lineEdit3->text();
    str4=ui->lineEdit4->text();
    str5=ui->lineEdit5->text();
    str6=ui->comboBox->currentText().trimmed();
    str7 = ui->comboBox_2->currentText().trimmed();
    str8=ui->lineEdit8->text();

    query.prepare("update storage_copy set 产品名称 = :two,产品编号 = :three,标签编号 = :four,数量 = :five,仓库 = :six,管理员 = :seven,入库时间 = :eight where 订单号 = :one");
    query.bindValue(":one",str1);
    query.bindValue(":two",str2);
    query.bindValue(":three",str3);
    query.bindValue(":four",str4);
    query.bindValue(":five",str5);
    query.bindValue(":six",str6);
    query.bindValue(":seven",str7);
    query.bindValue(":eight",str8);
    query.exec();
    if (query.isActive())
    {
        QMessageBox::information(this, tr("信息"), tr("订单信息修改成功！"));
        this->close();
    }
    else
    {
        QMessageBox::warning(this, tr("警告"), tr("订单信息修改失败！"));

    }

}
