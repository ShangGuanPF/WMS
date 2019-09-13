#include "product_modify2.h"
#include "ui_product_modify2.h"
#include<QSqlQueryModel>
#include<QSqlQuery>
#include<QDebug>
#include<QSqlRecord>
#include<QMessageBox>
#include<QDateEdit>

product_modify2::product_modify2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::product_modify2)
{
    ui->setupUi(this);
    this->setWindowTitle("产品信息修改");
     ui->pushButton->setShortcut(Qt::Key_Return);//将小键盘回车键与登录按钮绑定在一起
}

product_modify2::~product_modify2()
{
    delete ui;
}
void product_modify2::displayImformation(QString product_id)
{
    QSqlQuery query;
    query.exec("select *from product_imformation where 产品编号 = "+product_id+"");

    while(query.next())
    {
        ui->lineEdit->setText(query.value("产品编号").toString());
        ui->lineEdit_2->setText(query.value("产品名称").toString());
        ui->comboBox->setItemText(0,query.value("类别").toString());
        ui->comboBox_2->setItemText(0,query.value("单位").toString());
        ui->lineEdit_3->setText(query.value("数量").toString());
        ui->lineEdit_4->setText(query.value("进货价（元）").toString());
        ui->lineEdit_5->setText(query.value("批发价（元）").toString());
        ui->lineEdit_6->setText(query.value("零售价（元）").toString());
        ui->lineEdit_7->setText(query.value("生产厂商").toString());
         ui->lineEdit_8->setText(query.value("生产日期").toString());
         ui->lineEdit_9->setText(query.value("备注").toString());
    }
}

void product_modify2::on_pushButton_2_clicked()
{
    this->close();
}

void product_modify2::on_pushButton_clicked()
{
    QString select1 = ui->comboBox->currentText();
    QString select2 = ui->comboBox_2->currentText();
    if(select1=="请选择类别"||select2=="请选择单位")
        {
        QMessageBox::warning(this, tr("警告"), tr("未选择产品类别或单位！"));
    }
    else
        {
        QString str1,str2,str3,str4,str5,str6,str7,str8,str9,str10,str11;
        str1 = ui->lineEdit->text().trimmed();
        str2 = ui->lineEdit_2->text().trimmed();
        str3 = ui->comboBox->currentText().trimmed();
        str4 = ui->comboBox_2->currentText().trimmed();
        str5 = ui->lineEdit_3->text().trimmed();
        str6 = ui->lineEdit_4->text().trimmed();
        str7 = ui->lineEdit_5->text().trimmed();
        str8 = ui->lineEdit_6->text().trimmed();
        str9 = ui->lineEdit_7->text().trimmed();
        str10 = ui->lineEdit_8->text().trimmed();
        str11 = ui->lineEdit_9->text().trimmed();
        QSqlQuery query;
        query.exec("update product_imformation set 产品名称 = '"+str2+"',类别='"+str3+"',单位='"+str4+"',"
                         "数量='"+str5+"',进货价（元）='"+str6+"',批发价（元）='"+str7+"',零售价（元）='"+str8+"',"
                             "生产厂商='"+str9+"',生产日期='"+str10+"',备注='"+str11+"' where 产品编号 = '"+str1+"'");
        if (query.isActive())
        {
            QMessageBox::information(this, tr("信息"), tr("产品信息修改成功！"));
            this->close();
        }
        else
        {
            QMessageBox::warning(this, tr("警告"), tr("产品信息修改失败！"));

        }
    }

}
