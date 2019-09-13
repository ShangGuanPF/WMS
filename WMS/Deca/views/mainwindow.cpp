// -------------------------------------------------------------------------------------------------------------------
//
//  File: MainWindow.cpp
//
//  Copyright 2016 (c) Decawave Ltd, Dublin, Ireland.
//
//  All rights reserved.
//
//  Author:
//
// -------------------------------------------------------------------------------------------------------------------

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "connectionwidget.h"
#include "serialconnection.h"
#include "RTLSDisplayApplication.h"
#include "ViewSettings.h"
#include "login/administrator.h"

#include <QShortcut>
#include <QSettings>
#include <QDebug>
#include <QMessageBox>
#include <QDomDocument>
#include <QFile>
#include "wms/connect_database.h"

#include"storage_modify2.h"
#include"storage.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);



    ConnectDatabase::openDatabase();




    _showMainToolBar = false;
    _notConnected = true;

    {
        QWidget *empty = new QWidget(this);
        empty->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
        ui->mainToolBar->addWidget(empty);
    }

    _anchorConfigAction = new QAction(tr("&Connection Configuration"), this);
    //ui->menuBar->addAction(anchorConfigAction);
    //connect(anchorConfigAction, SIGNAL(triggered()), SLOT(onAnchorConfigAction()));

    createPopupMenu(ui->viewMenu);

    //add connection widget to the main window
    _cWidget = new ConnectionWidget(this);
    ui->mainToolBar->addWidget(_cWidget);
    administrator *admin=new administrator(this);
    ui->mainToolBar->addWidget(admin);

    QObject::connect(RTLSDisplayApplication::instance(), SIGNAL(aboutToQuit()), SLOT(saveSettings()));

    ui->helpMenu->addAction(ui->actionAbout);
    connect(ui->actionAbout, SIGNAL(triggered()), SLOT(onAboutAction()));

    _infoLabel = new QLabel(parent);

    ui->viewSettings_dw->close();
    ui->minimap_dw->close();

    connect(ui->minimap_dw->toggleViewAction(), SIGNAL(triggered()), SLOT(onMiniMapView()));

    QObject::connect(RTLSDisplayApplication::serialConnection(), SIGNAL(connectionStateChanged(SerialConnection::ConnectionState)),
                     this, SLOT(connectionStateChanged(SerialConnection::ConnectionState)));



   QObject::connect(graphicsWidget(),SIGNAL(sendsetting()),this,SLOT(show_settings()));//打开设置

   //历史轨迹--暂时
   QObject::connect(graphicsWidget(), SIGNAL(show_history(QString)), viewSettingsWidget(), SLOT(show_history(QString)));
   QObject::connect(graphicsWidget(), SIGNAL(unshow_history()), viewSettingsWidget(), SLOT(unshow_history()));



    RTLSDisplayApplication::connectReady(this, "onReady()");

}

void MainWindow::onReady()
{

    QObject::connect(graphicsWidget(), SIGNAL(setTagHistory(int)), viewSettingsWidget(), SLOT(setTagHistory(int)));

    QObject::connect(viewSettingsWidget(), SIGNAL(saveViewSettings(void)), this, SLOT(saveViewConfigSettings(void)));

    loadSettings();

    if(_showMainToolBar)
    {
        ui->mainToolBar->show();
    }
    else
    {
        ui->mainToolBar->hide();
    }
//stt
 //   ui->viewSettings_dw->show();
    ui->viewSettings_dw->hide();

#ifdef QT_DEBUG
    ui->mainToolBar->show();
#else
//    while(_notConnected)
//    {
//        if(_notConnected)
//        {
//            //QMessageBox::critical(NULL, tr("COM Error"), QString("Cannot open/connect to COM port.\nPlease make sure TREK device is connected to PC."));

//            QMessageBox::StandardButton reply;

//            //RTLSDisplayApplication::beep();

//            reply = QMessageBox::warning(this, tr("COM Error"), "Cannot open/connect to COM port.\n"
//                                          "Please make sure TREK device is connected to PC.\n\n "
//                                          "Press Close to exit or Retry to retry.",
//                                          QMessageBox::Close|QMessageBox::Retry);

//            if(reply == QMessageBox::Close)
//            {
//                //exit application
//                RTLSDisplayApplication::closeAllWindows();
//                exit(-1);
//            }

//            //else it will re-try...

//        }

//        if(_cWidget->updateDeviceList() > 0)
//        {
//            _notConnected = false;
//            break;
//        }
//    }
#endif
}

MainWindow::~MainWindow()
{
    delete ui;
}

GraphicsWidget *MainWindow::graphicsWidget()
{
    return ui->graphicsWidget;
}

ViewSettingsWidget *MainWindow::viewSettingsWidget()
{
    return ui->viewSettings_w;
}

QMenu *MainWindow::createPopupMenu()
{
    return createPopupMenu(new QMenu());
}

QMenu *MainWindow::createPopupMenu(QMenu *menu)
{
    menu->addAction(ui->viewSettings_dw->toggleViewAction());
    menu->addAction(ui->minimap_dw->toggleViewAction());

    return menu;
}

void MainWindow::onAnchorConfigAction()
{
    ui->mainToolBar->show();
}

void MainWindow::onMiniMapView()
{
    //check if we have loaded floorplan before we open mini map
    //if no floor plan close minimap
    QString path = RTLSDisplayApplication::viewSettings()->getFloorplanPath();

    if(path == "") //no floorplan loaded
    {
        ui->minimap_dw->close();
        //qDebug() << "close minimap" ;
        QMessageBox::warning(NULL, tr("Error"), "No floorplan loaded. Please upload floorplan to use mini-map.");
    }
}

void MainWindow::connectionStateChanged(SerialConnection::ConnectionState state)
{
    switch(state)
    {
        case SerialConnection::Connecting:
        {
            statusBar()->showMessage(QString("Connecting to Tag/Anchor..."));
            _showMainToolBar = false;
            _notConnected = false;
            break;
        }
        case SerialConnection::Connected:
        {
            statusBar()->showMessage("Connection successful.");
            loadSettings();
            _showMainToolBar = false;
            _notConnected = false;
            break;
        }
        case SerialConnection::ConnectionFailed:
        {
            statusBar()->showMessage("Connection failed.");
            loadSettings();
            _showMainToolBar = true;
            _notConnected = true;
            break;
        }
        case SerialConnection::Disconnected:
        {
            statusBar()->showMessage("Connection disconnected.");
            _showMainToolBar = true;
            _notConnected = true;
            break;
        }
    }

    if(state != SerialConnection::Connecting)
    {
        RTLSDisplayApplication::client()->setGWReady(true);
    }

#ifdef QT_DEBUG
    ui->mainToolBar->show();
#endif
}


void MainWindow::loadSettings()
{
    QSettings s;
    s.beginGroup("MainWindow");
    QVariant state = s.value("window-state");
    if (state.convert(QVariant::ByteArray))
    {
        this->restoreState(state.toByteArray());
    }

    QVariant geometry = s.value("window-geometry");
    if (geometry.convert(QVariant::ByteArray))
    {
        this->restoreGeometry(geometry.toByteArray());
    }
    else
    {
        this->showMaximized();
    }
    s.endGroup();

    //load view settings
    loadConfigFile("./TREKview_config.xml");
    graphicsWidget()->loadConfigFile("./TREKtag_config.xml");
    RTLSDisplayApplication::instance()->client()->loadConfigFile("./TREKanc_config.xml");
}

void MainWindow::saveViewConfigSettings(void)
{
    saveConfigFile("./TREKview_config.xml", "view_cfg");
}

void MainWindow::saveSettings()
{
    QSettings s;
    s.beginGroup("MainWindow");
    s.setValue("window-state",    this->saveState());
    s.setValue("window-geometry", this->saveGeometry());
    s.endGroup();

    //save view settings

    saveConfigFile("./TREKview_config.xml", "view_cfg");
    graphicsWidget()->saveConfigFile("./TREKtag_config.xml");
    RTLSDisplayApplication::instance()->client()->saveConfigFile("./TREKanc_config.xml");
}

void MainWindow::onAboutAction()
{
    _infoLabel->setText(tr("Invoked <b>Help|About</b>"));
    QMessageBox::about(this, tr("About"),
            tr("<b>CQUPT WMS</b>"
               "<br>version 1.2 </br> "
               "<br>2018.4.24</br>"
               ));
}

void MainWindow::loadConfigFile(QString filename)
{
    QFile file(filename);

    if (!file.open(QFile::ReadWrite | QFile::Text))
    {
        qDebug(qPrintable(QString("Error: Cannot read file %1 %2").arg(filename).arg(file.errorString())));
        return;
    }

    QDomDocument doc;

    doc.setContent(&file, false);

    QDomElement root = doc.documentElement();

    qDebug() << root.tagName() ;


    if( root.tagName() == "config" )
    {
        //there are acnhors saved in the config file
        //populate the _model anchor list

        QDomNode n = root.firstChild();
        while( !n.isNull() )
        {
            QDomElement e = n.toElement();
            if( !e.isNull() )
            {
                if( e.tagName() == "view_cfg" )
                {

                    RTLSDisplayApplication::viewSettings()->setGridWidth((e.attribute( "gridW", "" )).toDouble());
                    RTLSDisplayApplication::viewSettings()->setGridHeight((e.attribute( "gridH", "" )).toDouble());
                    RTLSDisplayApplication::viewSettings()->setShowGrid(((e.attribute( "gridS", "" )).toInt() == 1) ? true : false);
                    RTLSDisplayApplication::viewSettings()->setShowOrigin(((e.attribute( "originS", "" )).toInt() == 1) ? true : false);
                    RTLSDisplayApplication::viewSettings()->setFloorplanPath(e.attribute( "fplan", "" ));
                    RTLSDisplayApplication::viewSettings()->setFloorplanXOffset((e.attribute( "offsetX", "" )).toDouble());
                    RTLSDisplayApplication::viewSettings()->setFloorplanYOffset((e.attribute( "offsetY", "" )).toDouble());
                    RTLSDisplayApplication::viewSettings()->setFloorplanXScale((e.attribute( "scaleX", "" )).toDouble());
                    RTLSDisplayApplication::viewSettings()->setFloorplanYScale((e.attribute( "scaleY", "" )).toDouble());
                    RTLSDisplayApplication::viewSettings()->floorplanFlipX((e.attribute( "flipX", "" )).toInt());
                    RTLSDisplayApplication::viewSettings()->floorplanFlipY((e.attribute( "flipY", "" )).toInt());

                    RTLSDisplayApplication::viewSettings()->setFloorplanPathN();
                    RTLSDisplayApplication::viewSettings()->setSaveFP(((e.attribute( "saveFP", "" )).toInt() == 1) ? true : false);

                }
            }

            n = n.nextSibling();
        }

    }

    file.close(); //close the file
}

void MainWindow::saveConfigFile(QString filename, QString cfg)
{
    QFile file(filename);

    /*if (!file.open(QFile::ReadWrite | QFile::Text))
    {
        qDebug(qPrintable(QString("Error: Cannot read file %1 %2").arg(filename).arg(file.errorString())));
        return;
    }*/

    QDomDocument doc;
    //doc.setContent(&file, false);

    //save the graphical information
    QDomElement info = doc.createElement("config");
    doc.appendChild(info);

    qDebug() << info.tagName() ;

    if(cfg == "view_cfg")
    {
        QDomElement cn = doc.createElement( "view_cfg" );

        cn.setAttribute("gridW",  QString::number(RTLSDisplayApplication::viewSettings()->gridWidth(), 'g', 3));
        cn.setAttribute("gridH",  QString::number(RTLSDisplayApplication::viewSettings()->gridHeight(), 'g', 3));
        cn.setAttribute("gridS",  QString::number((RTLSDisplayApplication::viewSettings()->gridShow() == true) ? 1 : 0));
        cn.setAttribute("originS",  QString::number((RTLSDisplayApplication::viewSettings()->originShow() == true) ? 1 : 0));
        cn.setAttribute("saveFP",  QString::number((RTLSDisplayApplication::viewSettings()->floorplanSave() == true) ? 1 : 0));

        if(RTLSDisplayApplication::viewSettings()->floorplanSave()) //we want to save the floor plan...
        {
            cn.setAttribute("flipX",  QString::number(RTLSDisplayApplication::viewSettings()->floorplanFlipX(), 10));
            cn.setAttribute("flipY",  QString::number(RTLSDisplayApplication::viewSettings()->floorplanFlipY(), 10));
            cn.setAttribute("scaleX",  QString::number(RTLSDisplayApplication::viewSettings()->floorplanXScale(),'g', 3));
            cn.setAttribute("scaleY",  QString::number(RTLSDisplayApplication::viewSettings()->floorplanYScale(), 'g', 3));
            cn.setAttribute("offsetX",  QString::number(RTLSDisplayApplication::viewSettings()->floorplanXOffset(), 'g', 3));
            cn.setAttribute("offsetY",  QString::number(RTLSDisplayApplication::viewSettings()->floorplanYOffset(), 'g', 3));
            cn.setAttribute("fplan", RTLSDisplayApplication::viewSettings()->getFloorplanPath());
        }
        else
        {

        }
        info.appendChild( cn );

    }

    //file.close(); //close the file and overwrite with new info

    file.open(QIODevice::WriteOnly | QIODevice::Text);


    QTextStream ts( &file );
    ts << doc.toString();

    qDebug() << doc.toString();

    file.close();
}


void MainWindow::statusBarMessage(QString status)
{
    ui->statusBar->showMessage(status);
}

bool settings=false;
void MainWindow::show_settings(){
    if(settings==false)
    {
         ui->viewSettings_dw->show();
         settings=true;
    }
    else
    {
        ui->viewSettings_dw->hide();
        settings=false;
    }

}
