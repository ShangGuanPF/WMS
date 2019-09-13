#ifndef STAFF_MODIFY_H
#define STAFF_MODIFY_H


#include <QWidget>

namespace Ui {
class staff_modify;
}

class staff_modify : public QWidget
{
    Q_OBJECT

public:
    explicit staff_modify(QWidget *parent = 0);
    ~staff_modify();

private:
    Ui::staff_modify *ui;
    QString MODEL_STAFF = "staff_management";
private slots:
    void disPlayImformation(QString staff_id);
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
signals:
    void sendStaffID(QString);
};




#endif // STAFF_MODIFY_H
