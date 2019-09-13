#ifndef TAG_H
#define TAG_H

#include <QWidget>

namespace Ui {
class Tag;
}

class Tag : public QWidget
{
    Q_OBJECT

public:
    explicit Tag(QWidget *parent = 0);
    ~Tag();

private:
    Ui::Tag *ui;
};

#endif // TAG_H
