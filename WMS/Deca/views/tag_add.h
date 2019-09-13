#ifndef TAG_ADD_H
#define TAG_ADD_H

#include <QWidget>

namespace Ui {
class tag_add;
}

class tag_add : public QWidget
{
    Q_OBJECT

public:
    explicit tag_add(QWidget *parent = 0);
    ~tag_add();

private:
    Ui::tag_add *ui;
private slots:
    void showid(QString data,QString data2);

    void on_pushButton_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();
};

#endif // TAG_ADD_H
