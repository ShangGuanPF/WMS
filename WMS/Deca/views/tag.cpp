#include "tag.h"
#include "ui_tag.h"

Tag::Tag(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tag)
{
    ui->setupUi(this);
    this->setWindowTitle("增加标签");
     ui->pushButton->setShortcut(Qt::Key_Return);//将小键盘回车键与登录按钮绑定在一起

}

Tag::~Tag()
{
    delete ui;
}
