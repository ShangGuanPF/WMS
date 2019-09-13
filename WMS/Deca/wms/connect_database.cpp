#include "connect_database.h"
#include <QSqlQuery>
#include <QMessageBox>
QSqlDatabase ConnectDatabase::db = QSqlDatabase::addDatabase("QMYSQL");


ConnectDatabase::ConnectDatabase()
{

}


ConnectDatabase::~ConnectDatabase()
{

}

// Open the Database
bool ConnectDatabase::openDatabase()
{

    db.setHostName("mysql-wms.mysql.database.azure.com");
    db.setDatabaseName("wms");
    db.setUserName("summer@mysql-wms");
    db.setPassword("zx199461!");
    db.setPort(3306);

//    db.setHostName("localhost");
//    db.setDatabaseName("wms");
//    db.setUserName("root");
//    db.setPassword("199461");
//    db.setPort(3306);


    if (!db.open())
    {
       QMessageBox::information(NULL, QString("数据库错误提示"), QString("数据库连接失败"));
      //  printf("----------------------------------------database false-------------------------------\n");
        return false;
    }
    else
    {
       // printf("-------------------------------------database true--------------------\n");
    }
    return true;
}


// Close Database
void ConnectDatabase::closeDatabase()
{
    db.close();
}
