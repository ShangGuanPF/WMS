#ifndef STAFF_MODIFY2_H
#define STAFF_MODIFY2_H

#include <QWidget>

namespace Ui {
class staff_modify2;
}

class staff_modify2 : public QWidget
{
    Q_OBJECT

public:
    explicit staff_modify2(QWidget *parent = 0);
    ~staff_modify2();

private:
    Ui::staff_modify2 *ui;
private slots:
    void displayImformation(QString staff_id);
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
};

#endif // STAFF_MODIFY2_H
