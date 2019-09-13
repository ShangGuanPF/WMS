#include "add_store.h"
#include "ui_add_store.h"
#include<QSqlQuery>
#include<QDebug>
#include<QSqlQueryModel>
#include<QMessageBox>
#include<QSqlRecord>

add_store::add_store(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::add_store)
{
    ui->setupUi(this);
    this->setWindowTitle("新增仓库");
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("select 用户名 from staff_management");
    int rowNum = model->rowCount();
    for(int i = 0;i<rowNum;i++)
    {
        QString str = model->record(i).value(0).toString();
        ui->comboBox->addItem(str);
     }
    connect(ui->comboBox,SIGNAL(currentIndexChanged(QString)),this,SLOT(displayphone_num(QString)));
    setAttribute(Qt::WA_DeleteOnClose);
     ui->pushButton_2->setShortcut(Qt::Key_Return);//将小键盘回车键与登录按钮绑定在一起
}
void add_store::displayphone_num(QString staff_name)
{
    QSqlQuery query;
    query.exec("select 电话 from staff_management where 用户名='"+staff_name+"'");
    while(query.next())
    {
        ui->lineEdit_6->setText(query.value(0).toString());
    }
}
add_store::~add_store()
{
    delete ui;
}

void add_store::on_pushButton_3_clicked()
{
    this->close();
}

void add_store::on_pushButton_2_clicked()
{
    QString str1,str2,str3,str4,str5,str6,str7,str8,str9;
    str2 = ui->lineEdit_2->text().trimmed();
    str3 = ui->lineEdit_3->text().trimmed();
    str4 = ui->lineEdit_4->text().trimmed();
    str5 = ui->lineEdit_5->text().trimmed();
    str7 = ui->comboBox->currentText().trimmed();
    str6 = ui->lineEdit_7->text().trimmed();
    str8 = ui->lineEdit_9->text().trimmed();
    str9 = ui->lineEdit_6->text().trimmed();
    if(str2==NULL||str3==NULL||str4==NULL||str5==NULL||str7==NULL||str6==NULL||str9==NULL)
     {
           QMessageBox::warning(this, tr("警告"), tr("请将信息填写完整！"));
       }
     else
      {
            QSqlQuery query;
            query.prepare("insert into stores_management(仓库名称,仓库类型,现有库存,库存容量,状态,管理员,备注,联系电话)"
                       " values(:two,:three,:four,:five,:six,:seven,:eight,:nine)");
            query.bindValue(":two",str2);
            query.bindValue(":three",str3);
            query.bindValue(":four",str4);
            query.bindValue(":five",str5);
            query.bindValue(":six",str6);
            query.bindValue(":seven",str7);
            query.bindValue(":eight",str8);
            query.bindValue(":nine",str9);
            query.exec();
            if(query.isActive())
                {
                query.numRowsAffected();
                QMessageBox::information(this, tr("信息"), tr("仓库信息添加成功！"));
                this->close();
                }
            else
                QMessageBox::warning(this, tr("警告"), tr("添加失败！"));
        }


}

void add_store::on_pushButton_clicked()
{

    ui->lineEdit_2->setText(NULL);
    ui->lineEdit_3->setText(NULL);
    ui->lineEdit_4->setText(NULL);
    ui->lineEdit_5->setText(NULL);
    ui->lineEdit_7->setText(NULL);
    ui->lineEdit_6->setText(NULL);
    ui->lineEdit_9->setText(NULL);
}
