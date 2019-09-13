#ifndef STORAGE_DELETE_H
#define STORAGE_DELETE_H

#include <QWidget>

namespace Ui {
class storage_delete;
}

class storage_delete : public QWidget
{
    Q_OBJECT

public:
    ~storage_delete();
    explicit storage_delete(QWidget *parent = 0);

    static storage_delete* ShowWin()  //单例模式，只能产生一个窗口
    {
        if(Instance1==NULL)
            Instance1=new storage_delete();
        return Instance1;
    }
public slots:
    void disPlayImformation(QString value);

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();


private:
    Ui::storage_delete *ui;

    static storage_delete* Instance1;

};

#endif // STORAGE_DELETE_H
