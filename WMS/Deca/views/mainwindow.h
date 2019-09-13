// -------------------------------------------------------------------------------------------------------------------
//
//  File: MainWindow.h
//
//  Copyright 2016 (c) Decawave Ltd, Dublin, Ireland.
//
//  All rights reserved.
//
//  Author:
//
// -------------------------------------------------------------------------------------------------------------------

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAbstractSocket>
#include <QLabel>
#include "serialconnection.h"
#include <QSerialPort>

namespace Ui {
class MainWindow;
}

class SerialConnection;
class GraphicsWidget;
class ConnectionWidget;
class ViewSettingsWidget;
/**
 * The MainWindow class is the RTLS Controller Main Window widget.
 *
 * It is responsible for setting up all the dock widgets inside it, as weel as the central widget.
 * It also handles global shortcuts (Select All) and the Menu bar.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    GraphicsWidget *graphicsWidget();

    ViewSettingsWidget *viewSettingsWidget();

    /**
     * Create a new menu with the window's action
     * @see QMainWindow::createPopupMenu()
     * @return the new menu instance
     */
    virtual QMenu *createPopupMenu();

    /**
     * createPopupMenu adds the windows actions to \a menu.
     * The are the actions to hide or show dock widgets.
     * @param menu the QMenu instance to which the actions should be added
     * @return the menu object
     */
    QMenu *createPopupMenu(QMenu *menu);

    void saveConfigFile(QString filename, QString cfg);
    void loadConfigFile(QString filename);

public slots:
    void connectionStateChanged(SerialConnection::ConnectionState);
    void saveViewConfigSettings(void);

protected slots:
    void onReady();

    void loadSettings();
    void saveSettings();

    void onAboutAction();
    void onMiniMapView();

    void onAnchorConfigAction();

    void statusBarMessage(QString status);


    void show_settings();

private:
    Ui::MainWindow *const ui;
    QMenu *_helpMenu;
    QAction *_aboutAction;
    QLabel *_infoLabel;

    QAction *_anchorConfigAction;
    ConnectionWidget *_cWidget;

    bool _showMainToolBar;
    bool _notConnected;
};

#endif // MAINWINDOW_H
