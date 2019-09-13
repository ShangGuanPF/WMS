#ifndef CONNECT_DATABASE_H
#define CONNECT_DATABASE_H

#include <QSqlDatabase>


class ConnectDatabase
{
public:
    ConnectDatabase();
    ~ConnectDatabase();
    static bool openDatabase();
    static void closeDatabase();
private:
    static QSqlDatabase db;
};

#endif // CONNECT_DATABASE_H
