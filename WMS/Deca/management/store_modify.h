#ifndef STORE_MODIFY_H
#define STORE_MODIFY_H

#include <QWidget>

namespace Ui {
class store_modify;
}

class store_modify : public QWidget
{
    Q_OBJECT

public:
    explicit store_modify(QWidget *parent = 0);
    ~store_modify();

private:
    Ui::store_modify *ui;
signals:
    void sendStoreID(QString);
private slots:
    void disPlayImformation(QString store_id);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
};

#endif // STORE_MODIFY_H
