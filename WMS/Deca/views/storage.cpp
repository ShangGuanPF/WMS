#include "storage.h"
#include "ui_storage.h"
#include <QFont>
#include <QMessageBox>
#include <QString>
#include <QSqlQuery>
#include <QDateTime>
#include<QSqlTableModel>
#include<QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>
#include<QTableView>
#include<QDebug>
#include<QSqlRecord>
#include<QSerialPort>
#include "GraphicsWidget.h"
#include "wms/connect_database.h"

storage*  storage::Instance1=NULL;


storage::storage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::storage)
{
    ui->setupUi(this);
    this->setWindowTitle("货物入库");

    QSqlQuery query1;
    QSqlQueryModel *model = new QSqlQueryModel();
    query1.exec("select 姓名 from staff_management");

    while(query1.next())
    {
        QString str1 = query1.value(0).toString();
        ui->comboBox_2->addItem(str1);
     }
    model->setQuery("select 仓库名称 from stores_management");
    int rowNum = model->rowCount();
    for(int i = 0;i<rowNum;i++)
    {
        QString str2 = model->record(i).value(0).toString();
        ui->comboBox->addItem(str2);
     }
    /*
     * QSqlRelationalTableModel *model = new QSqlRelationalTableModel(this);
    model->setTable("storage_copy");
    model->setRelation(5,QSqlRelation("stores_management","仓库编号","仓库名称"));
    model->select();

   QTableView *view = new QTableView(this);
   view ->setModel(model);

    //ui->label_10->setItemDelegate(new setItemDelegate(ui->label_10));
*/
    setAttribute(Qt::WA_DeleteOnClose);


    ui->lineEdit_1->setText("自动生成订单号");
    ui->lineEdit_1->setEnabled(false);
     ui->pushButton->setShortcut(Qt::Key_Return);//将小键盘回车键与登录按钮绑定在一起
}

storage::~storage()
{
    delete ui;
}

void storage::on_pushButton_3_clicked()
{
    this->close();
}

void storage::on_pushButton_clicked()
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
    str1=ui->lineEdit_1->text().trimmed();
    str2=ui->lineEdit_2->text().trimmed();
    str3=ui->lineEdit_3->text().trimmed();
    str4=ui->lineEdit_4->text().trimmed();
    str5=ui->lineEdit_5->text().trimmed();
    str6=ui->comboBox->currentText().trimmed();
    str7=ui->comboBox_2->currentText().trimmed();
    QDateTime current_data=QDateTime::currentDateTime();
    QString current=current_data.toString("yyyy-MM-dd hh:mm:ss");
    str8=current;

    query.exec("select 订单号 from storage_copy where 订单号='"+str1+"'");
    if(!query.next())
    {
        //if(str1!=""&&str2!=""&&str3!=""&&str4!=""&&str5!=""&&str6!=""&&str7!=""&&str8!="")
        if(str2!=""&&str3!=""&&str4!=""&&str5!=""&&str6!=""&&str7!=""&&str8!="")
        {
            //query.prepare(tr("insert into storage_copy values(:two,:three,:four,:five,:six,:seven,:eight)"));
            query.prepare(tr("insert into storage_copy values(:one,:two,:three,:four,:five,:six,:seven,:eight)"));

            //query.bindValue(":one",str1);
            query.bindValue(":two",str2);
            query.bindValue(":three",str3);
            query.bindValue(":four",str4);
            query.bindValue(":five",str5);
            query.bindValue(":six",str6);
            query.bindValue(":seven",str7);
            query.bindValue(":eight",str8);
            query.exec();
            if(query.isActive())
            {
                query.numRowsAffected();
                QMessageBox::information(this, tr("信息"), tr("订单入库成功！"));
            }
            else
                QMessageBox::warning(this, tr("警告"), tr("入库失败！"));


        }
        else
            QMessageBox::warning(this, tr("警告"), tr("输入不能为空！"));

    }
    else
    {
        QMessageBox::warning(this, tr("警告"), tr("订单号是唯一的，不能重复！"));
        return ;
    }
   // ui->lineEdit_1->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    //ui->lineEdit_6->clear();
    //ui->lineEdit_7->clear();
    ui->lineEdit_6->clear();
    ui->lineEdit_7->clear();
    ui->lineEdit_9->clear();
    ui->lineEdit_10->clear();



}

void storage::on_pushButton_2_clicked()
{

   // ui->lineEdit_1->setText("");
    ui->lineEdit_2->setText("");
    ui->lineEdit_3->setText("");
    ui->lineEdit_4->setText("");
    ui->lineEdit_5->setText("");
    //ui->lineEdit_6->setText("");
    //ui->lineEdit_7->setText("");
    ui->lineEdit_8->setText("");
    ui->lineEdit_6->clear();
    ui->lineEdit_7->clear();
    ui->lineEdit_9->clear();
    ui->lineEdit_10->clear();
}

void storage::show_serialdata()//显示串口采集扫码器数据
{

    ConnectDatabase::openDatabase();
    QSqlQuery query;
    QString buf;
    char *buf_1;
    buf=GraphicsWidget::Serial->readAll().trimmed();
    QByteArray ba = buf.toLatin1(); // qstring to char
    buf_1=ba.data();
    QString name,type,unit1,data1,fc,num;
    if(strlen(buf_1)>5)
    {
        query.exec("select * from product_imformation where 产品编号 ='"+buf+"'");
        if(query.next())
        {
           QSqlRecord record=query.record();
           name=query.value(record.indexOf("产品名称")).toString();
           type=query.value(record.indexOf("类别")).toString();
           unit1=query.value(record.indexOf("单位")).toString();
           data1=query.value(record.indexOf("生产日期")).toString();
           fc=query.value(record.indexOf("生产厂商")).toString();
           num=query.value(record.indexOf("数量")).toString();

        }
        else
        {
             QMessageBox::warning(this, tr("警告"), tr("没有该商品编号，请先录入！"));
        }
        ui->lineEdit_2->setText(name);
        ui->lineEdit_3->setText(buf);
        ui->lineEdit_6->setText(type);
        ui->lineEdit_7->setText(unit1);
        ui->lineEdit_9->setText(data1);
        ui->lineEdit_10->setText(fc);
        ui->lineEdit_5->setText(num);

    }
    else
    {
        ui->lineEdit_4->setText(buf);
    }


}
