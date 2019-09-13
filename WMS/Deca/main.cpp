// -------------------------------------------------------------------------------------------------------------------
//
//  File: main.cpp
//
//  Copyright 2016 (c) Decawave Ltd, Dublin, Ireland.
//
//  All rights reserved.
//
//  Author:
//
// -------------------------------------------------------------------------------------------------------------------

#include "RTLSDisplayApplication.h"
#include "mainwindow.h"
#include "login/logindialog.h"
#include <QApplication>

/**
* @brief this is the application main entry point
*
*/
int main(int argc, char *argv[])
{
    QApplication::addLibraryPath("./plugins");
    RTLSDisplayApplication app(argc, argv);
    loginDialog lgn;
    if(lgn.exec()==QDialog::Accepted)
    {
        app.mainWindow()->show();
        app.setQuitOnLastWindowClosed(true);
        return app.QApplication::exec();
    }
    else
    {
       return 0;
   }


    app.mainWindow()->setAttribute(Qt::WA_QuitOnClose,true); //最后一个窗口关闭时关闭程序.


}
