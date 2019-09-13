// -------------------------------------------------------------------------------------------------------------------
//
//  File: RTLSDisplayApplication.cpp
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
#include "SerialConnection.h"
#include "RTLSClient.h"
#include "ViewSettings.h"
#include "GraphicsWidget.h"

#include <QMetaProperty>
#include <QDesktopWidget>

/**
* @brief RTLSDisplayApplication
*        Constructor, it initialises the application and its parts
*        the _serialConnection is used for managing the COM port connection
*        the _client consumes the data received over the COM port connection and sends the
* processed data to the graphical display
*        the _mainWindow holds the various GUI parts
*        the _viewSettings is used for configuration of the graphical display
*/
RTLSDisplayApplication::RTLSDisplayApplication(int &argc, char **argv) : QApplication(argc, argv)
{
    QDesktopWidget desktop;
    int desktopHeight=desktop.geometry().height();
    int desktopWidth=desktop.geometry().width();

    _ready = false;

    this->setOrganizationName("Decawave");
    this->setOrganizationDomain("decawave.com");
    this->setApplicationName("TREKDisplay");

    _viewSettings = new ViewSettings(this);

    _serialConnection = new SerialConnection(this);

    _client = new RTLSClient(this);

    _mainWindow = new MainWindow();
    _mainWindow->resize(desktopWidth/2,desktopHeight/2);

    _ready = true;

    //Connect the various signals and corresponding slots
    QObject::connect(_client, SIGNAL(anchPos(quint64,double,double,double,bool,bool)), graphicsWidget(), SLOT(anchPos(quint64,double,double,double,bool, bool)));
    QObject::connect(_client, SIGNAL(tagPos(quint64,double,double,double)), graphicsWidget(), SLOT(tagPos(quint64,double,double,double)));
    QObject::connect(_client, SIGNAL(tagStats(quint64,double,double,double,double)), graphicsWidget(), SLOT(tagStats(quint64,double,double,double,double)));
    QObject::connect(_client, SIGNAL(tagRange(quint64,quint64,double)), graphicsWidget(), SLOT(tagRange(quint64,quint64,double)));
    QObject::connect(_client, SIGNAL(statusBarMessage(QString)), _mainWindow, SLOT(statusBarMessage(QString)));

    QObject::connect(_client, SIGNAL(centerOnAnchors(void)), graphicsWidget(), SLOT(centerOnAnchors(void)));

    QObject::connect(_serialConnection, SIGNAL(clearTags()), graphicsWidget(), SLOT(clearTags()));

    QObject::connect(_serialConnection, SIGNAL(statusBarMessage(QString)), _mainWindow, SLOT(statusBarMessage(QString)));
    QObject::connect(_serialConnection, SIGNAL(connectionStateChanged(SerialConnection::ConnectionState)), _client, SLOT(connectionStateChanged(SerialConnection::ConnectionState)));

    QObject::connect(graphicsWidget(), SIGNAL(updateAnchorXYZ(int, int, double)), _client, SLOT(updateAnchorXYZ(int, int, double)));
    QObject::connect(graphicsWidget(), SIGNAL(updateTagCorrection(int, int, int)), _client, SLOT(updateTagCorrection(int, int, int)));

    QObject::connect(_client, SIGNAL(ancRanges(int, int, int)), graphicsWidget(), SLOT(ancRanges(int, int, int)));



    //tag查找
    QObject::connect(_client, SIGNAL(send_tag_position(quint64,double,double,double,double)), graphicsWidget(), SLOT(tag_position(quint64,double,double,double,double)));

    //emit ready signal so other components can finish initialisation
    emit ready();
}

RTLSDisplayApplication::~RTLSDisplayApplication()
{
    // Delete the objects manually, because we want to control the order
    delete _mainWindow;

    delete _client;

    delete _serialConnection;

	delete _viewSettings;
}

RTLSDisplayApplication *RTLSDisplayApplication::instance()
{
    return qobject_cast<RTLSDisplayApplication *>(QCoreApplication::instance());
}

ViewSettings *RTLSDisplayApplication::viewSettings()
{
    return instance()->_viewSettings;
}

RTLSClient *RTLSDisplayApplication::client()
{
    return instance()->_client;
}

SerialConnection *RTLSDisplayApplication::serialConnection()
{
    return instance()->_serialConnection;
}

MainWindow *RTLSDisplayApplication::mainWindow()
{
    return instance()->_mainWindow;
}

GraphicsWidget *RTLSDisplayApplication::graphicsWidget()
{
    return mainWindow()->graphicsWidget();
}

GraphicsView *RTLSDisplayApplication::graphicsView()
{
    return mainWindow()->graphicsWidget()->graphicsView();
}

void RTLSDisplayApplication::connectReady(QObject *receiver, const char *member, Qt::ConnectionType type)
{
    QMetaMethod method = receiver->metaObject()->method(receiver->metaObject()->indexOfMethod(QMetaObject::normalizedSignature(member)));
    // Either call the method or connect it to the ready signal

    if (instance()->_ready && method.isValid())
        method.invoke(receiver, type);
    else
        QObject::connect(instance(), QMetaMethod::fromSignal(&RTLSDisplayApplication::ready), receiver, method, type);
}

