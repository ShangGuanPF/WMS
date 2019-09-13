#ifndef STORAGE_MODIFY2_H
#define STORAGE_MODIFY2_H

#include <QWidget>
#include <QString>
namespace Ui {
class storage_modify2;
}

class storage_modify2 : public QWidget
{
    Q_OBJECT

public:
    explicit storage_modify2(QWidget *parent = 0);
    ~storage_modify2();

private:
    Ui::storage_modify2 *ui;
    QString order_id_global;
private slots:
    void displayAllInformation(QString data);

    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
};

#endif // STORAGE_MODIFY2_H
