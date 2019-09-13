#include "move_store.h"
#include "ui_move_store.h"
#include <QDesktopWidget>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include<QSqlRecord>

move_store::move_store(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::move_store)
{
    ui->setupUi(this);
    this->setWindowTitle("移库");
    model_storequery=new QSqlQueryModel(this);
    model_storagequery=new QSqlQueryModel(this);
    model_storequery->setQuery("select 仓库名称 from stores_management");
    int rowNum = model_storequery->rowCount();
    for(int i = 0;i<rowNum;i++)
    {
        QString str = model_storequery->record(i).value(0).toString();
        ui->comboBox->addItem(str);
     }
     ui->pushButton_2->setShortcut(Qt::Key_Return);//将小键盘回车键与登录按钮绑定在一起
}

move_store::~move_store()
{
    delete ui;
}
void move_store::display_imformation(QString num)
{
    QSqlQuery query;
    query.exec("select *from storage_copy where 订单号 = '"+num+"'");
    if(query.next())
    {
        ui->lineEdit->setText(query.value("订单号").toString());
        ui->lineEdit_2->setText(query.value("产品名称").toString());
        ui->lineEdit_3->setText(query.value("仓库").toString());
        ui->lineEdit_4->setText(query.value("数量").toString());
    }
}

void move_store::on_pushButton_clicked()
{
    this->close();
}


void move_store::on_pushButton_2_clicked()
{
    QString read_number = ui->lineEdit_5->text().trimmed();
    QString read_order = ui->lineEdit->text().trimmed();
    QString read_number_2 = ui->lineEdit_4->text().trimmed();
    QString store_new = ui->comboBox->currentText().trimmed();
    QString store_old = ui->lineEdit_3->text().trimmed();
    int read_num = read_number.toInt();
    int read_num2 = read_number_2.toInt();
    int store_num;
    QSqlQuery query;
    query.exec("select *from stores_management where 仓库名称='"+store_new+"'");
    if(query.next())
    {
         store_num = query.value("现有库存").toInt();
    }
    else
    {

    }
    if(store_new==store_old)
    {
        QMessageBox::information(this,tr("提醒信息"),tr("未移动仓库，所选仓库为当前仓库"));
    }
    else if(read_number=="")
    {
        QMessageBox::information(this,tr("提醒信息"),tr("请填写移库数量"));
    }
    else if(read_num>read_num2)
    {
        QMessageBox::warning(this, tr("警告"), tr("移库数量不能超过库存数量！"));
        ui->lineEdit_5->setText(NULL);
    }
    else
    {


        QString storage_number = QString::number(read_num2 - read_num);
        QString store_number = QString::number(store_num + read_num);
        QSqlQuery query_1,query_2;
        query_1.exec("update storage_copy set 数量 = '"+storage_number+"' where 订单号='"+read_order+"'");
        query_2.exec("update stores_management set 现有库存 = '"+store_number+"' where 仓库名称 = '"+store_new+"'");
        if (query.isActive())
        {
            QMessageBox::information(this, tr("信息"), tr("移库成功！"));
            this->close();
        }
        else
        {
            QMessageBox::warning(this, tr("警告"), tr("移库失败！"));
        }

    }
}
