#include "storage_modify.h"
#include "ui_storage_modify.h"
#include "storage_modify2.h"
#include <QDesktopWidget>
#include <QMessageBox>
#include <QSqlQuery>
#include <Qstring>

storage_modify* storage_modify::Instance1=NULL;


storage_modify::storage_modify(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::storage_modify)
{
    ui->setupUi(this);
    this->setWindowTitle("订单修改");
     ui->pushButton->setShortcut(Qt::Key_Return);//将小键盘回车键与登录按钮绑定在一起
}

storage_modify::~storage_modify()
{
    delete ui;
}
void storage_modify::disPlayImformation(QString value)
{

    ui->lineEdit->setText(value);
}

void storage_modify::on_pushButton_2_clicked()
{
    this->close();
}

void storage_modify::on_pushButton_clicked()
{
    QString order_id;
    QSqlQuery query;
    order_id=ui->lineEdit->text().trimmed();
    query.exec("select 订单号 from storage_copy where 订单号='"+order_id+"'");
    if(query.next())
    {
        storage_modify2 *modify = new storage_modify2();
        modify->show();
        modify->setAttribute(Qt::WA_QuitOnClose,false);//主窗口关闭时同时关闭该窗口

        modify->move((QApplication::desktop()->width() - modify->width()) / 2,
                  (QApplication::desktop()->height() - modify->height()) / 2);
        connect(this,SIGNAL(sendOrderID(QString)),modify,SLOT(displayAllInformation(QString)));
        emit sendOrderID(order_id);
        this->close();
    }
    else {
        QMessageBox::warning(this,tr("错误"),tr("没有该订单号，不能修改！"));
    }
}
