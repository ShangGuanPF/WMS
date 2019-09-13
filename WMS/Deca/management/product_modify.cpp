#include "product_modify.h"
#include "ui_product_modify.h"
#include "product_modify2.h"
#include <QDesktopWidget>
#include <QMessageBox>
#include <QSqlQuery>

product_modify::product_modify(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::product_modify)
{
    ui->setupUi(this);
    this->setWindowTitle("产品信息修改");
    setAttribute(Qt::WA_DeleteOnClose);//delete product_mdf
     ui->pushButton_2->setShortcut(Qt::Key_Return);//将小键盘回车键与登录按钮绑定在一起
}

product_modify::~product_modify()
{
    delete ui;
}
void product_modify::disPlayImformation(QString product_id)
{
    ui->lineEdit->setText(product_id);

}

void product_modify::on_pushButton_clicked()
{
    this->close();
}

void product_modify::on_pushButton_2_clicked()
{
    QSqlQuery query;
    QString product_id = ui->lineEdit->text().trimmed();
    query.exec("select 产品编号 from product_imformation where 产品编号 = '"+product_id+"'");
    if(query.next())
    {
        product_modify2 *product_mdf2 = new product_modify2();
        product_mdf2->setAttribute(Qt::WA_QuitOnClose,false);//主窗口关闭时同时关闭该窗口
        product_mdf2->move((QApplication::desktop()->width() - product_mdf2->width()) / 2,
                          (QApplication::desktop()->height() - product_mdf2->height()) / 2);//桌面正中
        product_mdf2->setWindowModality(Qt::ApplicationModal);//设置模态，禁止使用其他对话框
        product_mdf2->show();
        connect(this,SIGNAL(sendProductID(QString)),product_mdf2,SLOT(displayImformation(QString)));
        emit sendProductID(product_id);
        this->close();

    }
    else
    {

        QMessageBox::warning(this,tr("错误"),tr("请输入正确的产品编号！"));
    }
}
