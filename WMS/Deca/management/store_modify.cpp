#include "store_modify.h"
#include "ui_store_modify.h"
#include "store_modify2.h"
#include<QSqlQuery>
#include <QDesktopWidget>
#include <QMessageBox>

store_modify::store_modify(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::store_modify)
{
    ui->setupUi(this);
    this->setWindowTitle("仓库信息修改");
     ui->pushButton_2->setShortcut(Qt::Key_Return);//将小键盘回车键与登录按钮绑定在一起
    setAttribute(Qt::WA_DeleteOnClose);//delete store_mdf
}

store_modify::~store_modify()
{
    delete ui;
}
void store_modify::disPlayImformation(QString store_id)
{
    ui->lineEdit->setText(store_id);
}

void store_modify::on_pushButton_clicked()
{
    this->close();
}

void store_modify::on_pushButton_2_clicked()
{
    QSqlQuery query;
    QString store_id = ui->lineEdit->text().trimmed();
    query.exec("select 仓库编号 from stores_management where 仓库编号 = '"+store_id+"'");
    if(query.next())
    {
        store_modify2 *store_mdf2 = new store_modify2();
        store_mdf2->setAttribute(Qt::WA_QuitOnClose,false);//主窗口关闭时同时关闭该窗口
        store_mdf2->move((QApplication::desktop()->width() - store_mdf2->width()) / 2,
                          (QApplication::desktop()->height() - store_mdf2->height()) / 2);//桌面正中
        store_mdf2->setWindowModality(Qt::ApplicationModal);//设置模态，禁止使用其他对话框
        store_mdf2->show();
        connect(this,SIGNAL(sendStoreID(QString)),store_mdf2,SLOT(displayImformation(QString)));
        emit sendStoreID(store_id);
        this->close();

    }
    else
    {

        QMessageBox::warning(this,tr("错误"),tr("请输入正确的员工编号！"));
    }

}
