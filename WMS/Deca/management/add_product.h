#ifndef ADD_PRODUCT_H
#define ADD_PRODUCT_H

#include <QWidget>
#include <QSerialPort>

namespace Ui {
class add_product;
}

class add_product : public QWidget
{
    Q_OBJECT

public:
    explicit add_product(QWidget *parent = 0);
    ~add_product();
    static add_product* ShowWin()  //单例模式，只能产生一个窗口
    {
        if(Instance1==NULL)
            Instance1=new add_product();
        return Instance1;
    }

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::add_product *ui;
private:
    static add_product* Instance1;
};

#endif // ADD_PRODUCT_H
