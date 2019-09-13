#include "store_modify2.h"
#include "ui_store_modify2.h"
#include<QSqlQuery>
#include<QDebug>
#include<QSqlQueryModel>
#include<QMessageBox>
#include<QSqlRecord>

store_modify2::store_modify2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::store_modify2)
{
    ui->setupUi(this);
    this->setWindowTitle("仓库信息编辑");

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("select 用户名 from staff_management");
    int rowNum = model->rowCount();
    for(int i = 0;i<rowNum;i++)
    {
        QString str = model->record(i).value(0).toString();
        ui->comboBox->addItem(str);
     }
    connect(ui->comboBox,SIGNAL(currentIndexChanged(QString)),this,SLOT(displayphone_num(QString)));

     ui->pushButton_2->setShortcut(Qt::Key_Return);//将小键盘回车键与登录按钮绑定在一起
    setAttribute(Qt::WA_DeleteOnClose);
}
void store_modify2::displayphone_num(QString staff_name)
{
    QSqlQuery query;
    query.exec("select 电话 from staff_management where 用户名='"+staff_name+"'");
    while(query.next())
    {
        ui->lineEdit_7->setText(query.value(0).toString());
    }
}
store_modify2::~store_modify2()
{
    delete ui;
}
void store_modify2::displayImformation(QString store_id)
{
    QSqlQuery query;
    query.exec("select *from stores_management where 仓库编号 = "+store_id+"");

    while(query.next())
    {
        ui->lineEdit->setText(query.value("仓库编号").toString());
        ui->lineEdit_2->setText(query.value("仓库名称").toString());
        ui->lineEdit_3->setText(query.value("仓库类型").toString());
        ui->lineEdit_4->setText(query.value("现有库存").toString());
        ui->lineEdit_5->setText(query.value("库存容量").toString());
        ui->lineEdit_6->setText(query.value("状态").toString());
        ui->comboBox->setItemText(0,query.value("管理员").toString());
        ui->lineEdit_7->setText(query.value("联系电话").toString());
        ui->lineEdit_9->setText(query.value("备注").toString());
    }
}

void store_modify2::on_pushButton_3_clicked()
{
    this->close();
}


void store_modify2::on_pushButton_clicked()
{

    ui->lineEdit_2->setText(NULL);
    ui->lineEdit_3->setText(NULL);
    ui->lineEdit_4->setText(NULL);
    ui->lineEdit_5->setText(NULL);
    ui->lineEdit_6->setText(NULL);
    ui->lineEdit_7->setText(NULL);
    ui->lineEdit_9->setText(NULL);
}

void store_modify2::on_pushButton_2_clicked()
{
    QString select = ui->comboBox->currentText();
    if(select == "请选择管理员")
        {
        QMessageBox::warning(this, tr("警告"), tr("请选择管理员！"));
    }
    else
    {
        QString str1,str2,str3,str4,str5,str6,str7,str8,str9;
        str1 = ui->lineEdit->text().trimmed();
        str2 = ui->lineEdit_2->text().trimmed();
        str3 = ui->lineEdit_3->text().trimmed();
        str4 = ui->lineEdit_4->text().trimmed();
        str5 = ui->lineEdit_5->text().trimmed();
        str6 = ui->lineEdit_6->text().trimmed();
        str8 = ui->lineEdit_7->text().trimmed();
        str9 = ui->lineEdit_9->text().trimmed();
        str7 = ui->comboBox->currentText().trimmed();

        QSqlQuery query;
        query.exec("update stores_management set 仓库名称 = '"+str2+"',仓库类型='"+str3+"',现有库存='"+str4+"',"
                         "库存容量='"+str5+"',状态='"+str6+"',管理员='"+str7+"',联系电话='"+str8+"',备注='"+str9+"' where 仓库编号 = '"+str1+"'");
        if (query.isActive())
        {
            QMessageBox::information(this, tr("信息"), tr("仓库信息修改成功！"));
            this->close();
        }
        else
        {
            QMessageBox::warning(this, tr("警告"), tr("请将信息修改完整！"));

        }
    }

}
