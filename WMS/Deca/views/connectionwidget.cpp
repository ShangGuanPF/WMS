// -------------------------------------------------------------------------------------------------------------------
//
//  File: ConnectionWidget.cpp
//
//  Copyright 2016 (c) Decawave Ltd, Dublin, Ireland.
//
//  All rights reserved.
//
//  Author:
//
// -------------------------------------------------------------------------------------------------------------------

#include "connectionwidget.h"
#include "ui_connectionwidget.h"

#include "RTLSDisplayApplication.h"
#include "mainwindow.h"

#include <QSettings>
#include <QDebug>

ConnectionWidget::ConnectionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConnectionWidget)
{
    ui->setupUi(this);

    QObject::connect(ui->connect_pb, SIGNAL(clicked()), SLOT(connectButtonClicked()));  //add a function for the Connect button click

    this->show();
#ifdef QT_DEBUG
    ui->connect_pb->setEnabled(true);
    ui->label->setEnabled(true);
    ui->comPort->setEnabled(true);
#else
    ui->connect_pb->setEnabled(false);
    ui->label->setEnabled(false);
    ui->comPort->setEnabled(false);
#endif
    _selected = 0;

    RTLSDisplayApplication::connectReady(this, "onReady()");
}

void ConnectionWidget::onReady()
{
    QObject::connect(RTLSDisplayApplication::serialConnection(), SIGNAL(connectionStateChanged(SerialConnection::ConnectionState)),
                     this, SLOT(connectionStateChanged(SerialConnection::ConnectionState)));

    updateDeviceList();

    connectionStateChanged(SerialConnection::Disconnected);
}

ConnectionWidget::~ConnectionWidget()
{
    delete ui;
}

int ConnectionWidget::updateDeviceList()
{
    int count  = 0;
    qDebug() << "ConnectionWidget::updateDeviceList";

    //remove all items from the combobox
    while(ui->comPort->count())
    {
        ui->comPort->removeItem(0);
    }

    RTLSDisplayApplication::serialConnection()->findSerialDevices();

    ui->comPort->addItems(RTLSDisplayApplication::serialConnection()->portsList());

    count = ui->comPort->count();

    //check if we have found any TREK devices in the COM ports list
    if(count == 0)
    {
        ui->connect_pb->setEnabled(false);
        ui->label->setEnabled(false);
        ui->comPort->setEnabled(false);

        connectionStateChanged(SerialConnection::Disconnected);
        RTLSDisplayApplication::mainWindow()->connectionStateChanged(SerialConnection::Disconnected);
    }
    else
    {
#ifdef QT_DEBUG

#else
        //connect to the first TREK device
        if(RTLSDisplayApplication::serialConnection()->openConnection(0) != 0)
        {
            return -1;
        }
#endif
    }

    return count;
}

void ConnectionWidget::serialError(void)
{
    ui->connect_pb->setEnabled(false);
    ui->label->setEnabled(false);
    ui->comPort->setEnabled(false);
}


void ConnectionWidget::connectButtonClicked()
{
    switch (_state)
    {
    case SerialConnection::Disconnected:
    case SerialConnection::ConnectionFailed:
    {
        RTLSDisplayApplication::serialConnection()->openConnection(ui->comPort->currentIndex());
        break;
    }

    case SerialConnection::Connecting:
        RTLSDisplayApplication::serialConnection()->cancelConnection();
        break;

    case SerialConnection::Connected:
        RTLSDisplayApplication::serialConnection()->closeConnection();
        break;
    }
}

void ConnectionWidget::connectionStateChanged(SerialConnection::ConnectionState state)
{
    this->_state = state;
    switch(state)
    {
    case SerialConnection::Disconnected:
    case SerialConnection::ConnectionFailed:
        ui->connect_pb->setText("Connect");
        this->show();
        break;

    case SerialConnection::Connecting:
        ui->connect_pb->setText("Cancel");
        this->show();
        break;

    case SerialConnection::Connected:
        ui->connect_pb->setText("Disconnect");
        this->hide();
        break;
    }

    bool enabled = (state == SerialConnection::Disconnected || state == SerialConnection::ConnectionFailed) ? true : false;
    //can change the COM port once not opened
    ui->comPort->setEnabled(enabled);
}



