// -------------------------------------------------------------------------------------------------------------------
//
//  File: SerialConnection.cpp
//
//  Copyright 2016 (c) Decawave Ltd, Dublin, Ireland.
//
//  All rights reserved.
//
//  Author:
//
// -------------------------------------------------------------------------------------------------------------------

#include "SerialConnection.h"

#include <QDebug>
#include <QSerialPortInfo>
#include <QMessageBox>

#define DEVICE_STR ("STMicroelectronics Virtual COM Port")
#define INST_REPORT_LEN   (65)
#define INST_REPORT_LEN_HEADER (20)
#define INST_VERSION_LEN  (16)
#define INST_CONFIG_LEN   (1)

SerialConnection::SerialConnection(QObject *parent) :
    QObject(parent)
{
    _serial = new QSerialPort(this);

    connect(_serial, SIGNAL(error(QSerialPort::SerialPortError)), this,
            SLOT(handleError(QSerialPort::SerialPortError)));

    connect(_serial, SIGNAL(readyRead()), this, SLOT(readData()));

    _processingData = true;

}

SerialConnection::~SerialConnection()
{
    if(_serial->isOpen())
        _serial->close();

    delete _serial;
}

QStringList SerialConnection::portsList()
{
    return _ports;
}

void SerialConnection::findSerialDevices()
{
    _portInfo.clear();
    _ports.clear();

    foreach (const QSerialPortInfo &port, QSerialPortInfo::availablePorts())
    //for (QSerialPortInfo port : QSerialPortInfo::availablePorts())
    {
        //Their is some sorting to do for just list the port I want, with vendor Id & product Id
        qDebug() << port.portName() << port.vendorIdentifier() << port.productIdentifier()
                 << port.hasProductIdentifier() << port.hasVendorIdentifier() << port.isBusy()
                 << port.manufacturer() << port.description();


        if(port.description() == DEVICE_STR)
        {
            _portInfo += port;
            _ports += port.portName();
        }
    }
}

int SerialConnection::openSerialPort(QSerialPortInfo x)
{
    int error = 0;
    _serial->setPort(x);

    if(!_serial->isOpen())
    {
        if (_serial->open(QIODevice::ReadWrite))
        {
            _serial->setBaudRate(QSerialPort::Baud115200/*p.baudRate*/);
            _serial->setDataBits(QSerialPort::Data8/*p.dataBits*/);
            _serial->setParity(QSerialPort::NoParity/*p.parity*/);
            _serial->setStopBits(QSerialPort::OneStop/*p.stopBits*/);
            _serial->setFlowControl(QSerialPort::NoFlowControl /*p.flowControl*/);


            emit statusBarMessage(tr("Connected to %1").arg(x.portName()));

            qDebug() << "send \"decA$\"" ;
            writeData("deca$q");
            //writeData("deca?");

            //emit serialOpened(); - wait until we get reply from the unit

        }
        else
        {
            //QMessageBox::critical(NULL, tr("Error"), _serial->errorString());

            emit statusBarMessage(tr("Open error"));

            qDebug() << "Serial error: " << _serial->error();

            _serial->close();

            emit serialError();

            error = 1;
        }
    }
    else
    {
        qDebug() << "port already open!";

        error = 0;
    }

    return error;
}

int SerialConnection::openConnection(int index)
{
    QSerialPortInfo x;
    int foundit = -1;
    int open = false;

    foreach (const QSerialPortInfo &port, QSerialPortInfo::availablePorts())
    {
        if(port.description() == DEVICE_STR)
        {
            foundit++;
            if(foundit==index)
            {
                x = port;
                open = true;
                break;
            }
        }
    }

    qDebug() << "is busy? " << x.isBusy() << "index " << index << " = found " << foundit;

    if(!open) return -1;

    qDebug() << "open serial port " << index << x.portName();

    //open serial port
    return openSerialPort(x);
}

void SerialConnection::closeConnection()
{
    _serial->close();
    emit statusBarMessage(tr("COM port Disconnected"));
    emit connectionStateChanged(Disconnected);

    _processingData = true;
}

void SerialConnection::writeData(const QByteArray &data)
{
    if(_serial->isOpen())
    {
        _serial->write(data);
        //waitForData = true;
    }
    else
    {
        qDebug() << "not open - can't write?";
    }

    emit connectionStateChanged(Connected);
}


void SerialConnection::cancelConnection()
{
    emit connectionStateChanged(ConnectionFailed);
}


void SerialConnection::readData(void)
{
    if(_processingData)
    {
        QByteArray data = _serial->readAll();
        int length = data.length();
        int offset = 0;

        if(length >= INST_REPORT_LEN_HEADER)
        {
            qDebug() << length << '=' << data ;

            while(length >= INST_REPORT_LEN_HEADER)
            {
                QByteArray header = data.mid(offset, 2);

                qDebug() << header ;
                if(header.contains("nV")) //loop here until we reach header ("nV")
                {
                    break;
                }

                //NOTE: ma = anchor to anchor ranging report
                //      mr = tag to anchor ranging report (raw)
                //      mc = tag to anchor ranging report (range bias corrected)
                if(header.contains("ma")) //we have found start of range report message - remove it from the data buffer
                {
                    offset += INST_REPORT_LEN;
                    length -= INST_REPORT_LEN;
                }
                else if(header.contains("mr")) //we have found start of range report message - remove it from the data buffer
                {
                    offset += INST_REPORT_LEN;
                    length -= INST_REPORT_LEN;
                }
                else if(header.contains("mc")) //we have found start of range report message - remove it from the data buffer
                {
                    offset += INST_REPORT_LEN;
                    length -= INST_REPORT_LEN;
                }
                else //just remove 2 bytes and look for "nV" or "ma"
                {
                    offset += 2;
                    length -= 2;
                }
            }

            if(length < INST_REPORT_LEN_HEADER)
            {
                if(_serial->isOpen())
                {
                    _serial->write("decA$");
                }
                return;
            }

            QByteArray instanceVer = data.mid(offset+1, INST_VERSION_LEN);
            QByteArray instanceConf = data.mid(offset+1+INST_VERSION_LEN, INST_CONFIG_LEN);

            //NOTE - only TREK rev 2.0+ is supported by this GUI
            //e.g. nVersion X.Y TREKZ
            _conncectionConfig = QString::fromLocal8Bit(instanceConf, INST_CONFIG_LEN);
            _connectionVersion = QString::fromLocal8Bit(instanceVer, INST_VERSION_LEN);

            _processingData = false;

            qDebug() << _conncectionConfig <<  _connectionVersion << instanceConf;

            emit serialOpened(_connectionVersion, _conncectionConfig);
        }
    }
}

void SerialConnection::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        //QMessageBox::critical(this, tr("Critical Error"), serial->errorString());
        _serial->close();

        _processingData = true;
    }
}


