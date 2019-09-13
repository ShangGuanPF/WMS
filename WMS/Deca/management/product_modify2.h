#ifndef PRODUCT_MODIFY2_H
#define PRODUCT_MODIFY2_H

#include <QWidget>

namespace Ui {
class product_modify2;
}

class product_modify2 : public QWidget
{
    Q_OBJECT

public:
    explicit product_modify2(QWidget *parent = 0);
    ~product_modify2();

private:
    Ui::product_modify2 *ui;
private slots:
    void displayImformation(QString product_id);
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
};

#endif // PRODUCT_MODIFY2_H
