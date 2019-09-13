#ifndef PRODUCT_MODIFY_H
#define PRODUCT_MODIFY_H

#include <QWidget>

namespace Ui {
class product_modify;
}

class product_modify : public QWidget
{
    Q_OBJECT

public:
    explicit product_modify(QWidget *parent = 0);
    ~product_modify();

private:
    Ui::product_modify *ui;

private slots:
    void disPlayImformation(QString product_id);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
signals:
    void sendProductID(QString);
};

#endif // PRODUCT_MODIFY_H
