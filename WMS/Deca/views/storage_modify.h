#ifndef STORAGE_MODIFY_H
#define STORAGE_MODIFY_H

#include <QWidget>
#include <QString>
namespace Ui {
class storage_modify;
}

class storage_modify : public QWidget
{
    Q_OBJECT

public:
    ~storage_modify();
    explicit storage_modify(QWidget *parent = 0);
    static storage_modify* ShowWin()  //单例模式，只能产生一个窗口
    {
        if(Instance1==NULL)
            Instance1=new storage_modify();
        return Instance1;
    }

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();
    void disPlayImformation(QString value);

private:
    Ui::storage_modify *ui;

    static storage_modify* Instance1;
signals:
    void sendOrderID(QString);

};

#endif // STORAGE_MODIFY_H
