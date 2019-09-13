#ifndef MOVE_STORE_H
#define MOVE_STORE_H

#include <QWidget>
#include<QSqlQueryModel>

namespace Ui {
class move_store;
}

class move_store : public QWidget
{
    Q_OBJECT

public:
    explicit move_store(QWidget *parent = 0);
    ~move_store();

private:
    Ui::move_store *ui;
    QSqlQueryModel *model_storequery;
    QSqlQueryModel *model_storagequery;
private slots:
    void display_imformation(QString num);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
};

#endif // MOVE_STORE_H
