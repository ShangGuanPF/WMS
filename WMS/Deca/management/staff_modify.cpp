#include "staff_modify.h"
#include "ui_staff_modify.h"
#include<qdebug.h>
#include "staff_modify2.h"
#include <QDesktopWidget>
#include <QMessageBox>
#include <QSqlQuery>

staff_modify::staff_modify(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::staff_modify)
{
    ui->setupUi(this);
    this->setWindowTitle("员工信息修改");
     ui->pushButton->setShortcut(Qt::Key_Return);//将小键盘回车键与登录按钮绑定在一起
   // setAttribute(Qt::WA_DeleteOnClose);//delete staff_mdf
}

staff_modify::~staff_modify()
{
    delete ui;
}
void staff_modify::disPlayImformation(QString staff_id)
{
    ui->lineEdit->setText(staff_id);

}

void staff_modify::on_pushButton_2_clicked()
{
    this->close();
}

void staff_modify::on_pushButton_clicked()
{
    QSqlQuery query;
    QString staff_id = ui->lineEdit->text().trimmed();
    query.exec("select 员工编号 from "+MODEL_STAFF+" where 员工编号 = '"+staff_id+"'");
    if(query.next())
    {
        staff_modify2 *staff_mdf2 = new staff_modify2();
        staff_mdf2->setAttribute(Qt::WA_QuitOnClose,false);//主窗口关闭时同时关闭该窗口
        staff_mdf2->move((QApplication::desktop()->width() - staff_mdf2->width()) / 2,
                          (QApplication::desktop()->height() - staff_mdf2->height()) / 2);//桌面正中
        staff_mdf2->setWindowModality(Qt::ApplicationModal);//设置模态，禁止使用其他对话框
        staff_mdf2->show();
        connect(this,SIGNAL(sendStaffID(QString)),staff_mdf2,SLOT(displayImformation(QString)));
        emit sendStaffID(staff_id);
        this->close();

    }
    else
    {

        QMessageBox::warning(this,tr("错误"),tr("请输入正确的员工编号！"));
    }


}
