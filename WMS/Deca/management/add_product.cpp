#include "add_product.h"
#include "ui_add_product.h"
#include "GraphicsWidget.h"
#include<QSqlQuery>
#include<QDebug>
#include<QSqlQueryModel>
#include<QMessageBox>
#include<QSqlRecord>
add_product*  add_product::Instance1=NULL;
add_product::add_product(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::add_product)
{
    ui->setupUi(this);
    this->setWindowTitle("新增产品信息");
    ui->dateEdit->setDisplayFormat("yyyy/MM/dd");
     ui->pushButton_2->setShortcut(Qt::Key_Return);//将小键盘回车键与登录按钮绑定在一起
}

add_product::~add_product()
{
    delete ui;
}

void add_product::on_pushButton_clicked()
{
    this->close();
}

void add_product::on_pushButton_2_clicked()
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
    str9 = ui->dateEdit->text().trimmed();
    str10 = ui->lineEdit_8->text().trimmed();
    str11 = ui->lineEdit_9->text().trimmed();
    if(str3=="请选择类别"||str4=="请选择单位")
        {
        QMessageBox::warning(this, tr("警告"), tr("请选择产品类别或单位！"));
    }
    else
    {
        QSqlQuery query1;
        query1.exec("select *from product_imformation where 产品编号='"+str1+"'");
        if(query1.next())
        {
            QMessageBox::warning(this, tr("警告"), tr("产品编号重复！"));
            ui->lineEdit->setText(NULL);
        }
        else
        {
            if(str1==NULL||str2==NULL||str3==NULL||str4==NULL||str5==NULL||str6==NULL||str7==NULL||str8==NULL||str9==NULL||str10==NULL)
            {
                QMessageBox::warning(this, tr("警告"), tr("请将信息填写完整！"));
            }
            else
            {
                QSqlQuery query;
                query.prepare("insert into product_imformation(产品编号,产品名称,类别,单位,数量,进货价（元）,批发价（元）,零售价（元）,生产日期,生产厂商,备注)"
                           " values(:one,:two,:three,:four,:five,:six,:seven,:eight,:nine,:ten,:eleven)");
                query.bindValue(":one",str1);
                query.bindValue(":two",str2);
                query.bindValue(":three",str3);
                query.bindValue(":four",str4);
                query.bindValue(":five",str5);
                query.bindValue(":six",str6);
                query.bindValue(":seven",str7);
                query.bindValue(":eight",str8);
                query.bindValue(":nine",str9);
                query.bindValue(":ten",str10);
                query.bindValue(":eleven",str11);
                query.exec();
                if(query.isActive())
                    {
                    query.numRowsAffected();
                    QMessageBox::information(this, tr("信息"), tr("产品信息添加成功！"));
                    this->close();
                    }
                else
                    QMessageBox::warning(this, tr("警告"), tr("添加失败！"));
            }

        }
    }

}

