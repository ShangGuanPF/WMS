// -------------------------------------------------------------------------------------------------------------------
//
//  File: RTLSDisplayApplication.h
//
//  Copyright 2016 (c) Decawave Ltd, Dublin, Ireland.
//
//  All rights reserved.
//
//  Author:
//
// -------------------------------------------------------------------------------------------------------------------

#ifndef RTLSDISPLAYAPPLICATION_H
#define RTLSDISPLAYAPPLICATION_H

#include <QApplication>
#include <QAbstractItemView>
#include <qthread.h>

class QItemSelectionModel;
class ViewSettings;
class MainWindow;
class SerialConnection;
class GraphicsWidget;
class GraphicsView;
class RTLSClient;

/**
 * The RTLSDisplayApplication class is a singleton class which handles the application.
 *
 * It allows getting pointers to global objects within the application.
 * These pointers should not be used during initial initialization (in constructors), as it is niot guaranteed that they have bben allocated and initialized yet.\n
 * Instead, any setup which requires these pointers should be split in another function.\n
 * connectReady() may be used to run that specific function once all the resources are allocated.
 * The slot passed as the second argument will either run immediately if setup is already done, or connected to a signal that will be emitted once initialization is complete.
 * @code
 * RTLSDisplayApplication::connectReady(this, "onReady()");
 * @endcode
 *
 */
class RTLSDisplayApplication : public QApplication  //, virtual public QThread
{
    Q_OBJECT
public:
    explicit RTLSDisplayApplication(int &argc, char ** argv);
    virtual ~RTLSDisplayApplication();

    static RTLSDisplayApplication *instance();
	static ViewSettings *viewSettings();

    static SerialConnection *serialConnection();
    static RTLSClient *client();
    static MainWindow *mainWindow();

    static GraphicsWidget *graphicsWidget();
    static GraphicsView *graphicsView();

    /**
     * Call \a member of \a receiver once initialization is complete.
     * The function is either called reight away if initialization is already done, or connected to the ready() signal.
     * The method must be registered within Qt's meta object system, using Q_INVOKABLE, or declaring it as a slot.
     */
    static void connectReady(QObject *receiver, const char *member, Qt::ConnectionType type = Qt::AutoConnection);

signals:
    /**
     * Emitted when the inizialization is complete.
     * Because this signal is only emitted once at application startup, the connectReady() should be used instead.
     */
    void ready();

public slots:

protected:

private:
	ViewSettings *_viewSettings;

    SerialConnection *_serialConnection;

    RTLSClient *_client;

    MainWindow *_mainWindow;

    bool _ready;
};

#endif // RTLSDISPLAYAPPLICATION_H
