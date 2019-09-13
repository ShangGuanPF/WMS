#ifndef STORE_MODIFY2_H
#define STORE_MODIFY2_H

#include <QWidget>

namespace Ui {
class store_modify2;
}

class store_modify2 : public QWidget
{
    Q_OBJECT

public:
    explicit store_modify2(QWidget *parent = 0);
    ~store_modify2();

private:
    Ui::store_modify2 *ui;
private slots:
    void displayImformation(QString store_id);
    void on_pushButton_3_clicked();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void displayphone_num(QString staff_name);
};

#endif // STORE_MODIFY2_H
