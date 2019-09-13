#-------------------------------------------------
#
# Project created by QtCreator 2014-05-28T11:50:00
#
#-------------------------------------------------
cache()

QT       += core gui network xml serialport
QT += core gui widgets

RC_ICONS=CQUPT.ico

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DecaRangeRTLS
TEMPLATE = app
QMAKE_INFO_PLIST = Info.plist

INCLUDEPATH += models network views util tools

INCLUDEPATH += $$PWD/armadillo-3.930.0/include


LIBS += -L$$PWD/armadillo-3.930.0/lib/ -lblas_win32_MT

LIBS += -L$$PWD/armadillo-3.930.0/lib/ -llapack_win32_MT

SOURCES += main.cpp\
    RTLSDisplayApplication.cpp \
    views/mainwindow.cpp \
    network/RTLSClient.cpp \
    views/GraphicsView.cpp \
    views/GraphicsWidget.cpp \
    views/ViewSettingsWidget.cpp \
	views/MinimapView.cpp \
    views/connectionwidget.cpp \
    models/ViewSettings.cpp \
    tools/OriginTool.cpp \
    tools/RubberBandTool.cpp \
    tools/ScaleTool.cpp \
    util/QPropertyModel.cpp \
    network/SerialConnection.cpp \
    tools/trilateration.cpp \
    wms/connect_database.cpp \
    views/storage.cpp \
    views/storage_modify.cpp \
    views/storage_modify2.cpp \
    views/storage_delete.cpp \
    views/tag_add.cpp \
    management/product_modify.cpp \
    management/staff_modify.cpp \
    management/store_modify.cpp \
    management/add_staff.cpp \
    management/staff_modify2.cpp \
    management/store_modify2.cpp \
    management/product_modify2.cpp \
    management/add_store.cpp \
    management/add_product.cpp \
    login/logindialog.cpp \
    login/administrator.cpp \
    login/find_password.cpp \
    login/find_result.cpp \
    login/modify_password.cpp \
    views/move_store.cpp

HEADERS  += \
    RTLSDisplayApplication.h \
	views/mainwindow.h \
    network/RTLSClient.h \
    views/GraphicsView.h \
    views/GraphicsWidget.h \
    views/ViewSettingsWidget.h \
    views/MinimapView.h \
    views/connectionwidget.h \
    models/ViewSettings.h \
    tools/AbstractTool.h \
    tools/OriginTool.h \
    tools/RubberBandTool.h \
    tools/ScaleTool.h \
    util/QPropertyModel.h \
    network/SerialConnection.h \
    tools/trilateration.h \
    wms/connect_database.h \
    views/storage.h \
    views/storage_modify.h \
    views/storage_modify2.h \
    views/storage_delete.h \
    views/tag_add.h \
    management/product_modify.h \
    management/store_modify.h \
    management/staff_modify.h \
    management/add_staff.h \
    management/staff_modify2.h \
    management/store_modify2.h \
    management/product_modify2.h \
    management/add_store.h \
    management/add_product.h \
    login/logindialog.h \
    login/administrator.h \
    login/find_password.h \
    login/find_result.h \
    login/modify_password.h \
    views/move_store.h
FORMS    += \
    views/mainwindow.ui \
    views/GraphicsWidget.ui \
    views/ViewSettingsWidget.ui \
    views/connectionwidget.ui \
    views/storage.ui \
    views/storage_modify.ui \
    views/storage_modify2.ui \
    views/storage_delete.ui \
    views/tag_add.ui \
    management/product_modify.ui \
    management/staff_modify.ui \
    management/store_modify.ui \
    management/add_staff.ui \
    management/staff_modify2.ui \
    management/store_modify2.ui \
    management/product_modify2.ui \
    management/add_store.ui \
    management/add_product.ui \
    login/logindialog.ui \
    login/administrator.ui \
    login/find_password.ui \
    login/find_result.ui \
    login/modify_password.ui \
    views/move_store.ui


RESOURCES += \
    res/resources.qrc
    QT   +=sql



CONFIG += qaxcontainer #导出excel
QT+ =serialport
QT       += core gui multimedia multimediawidgets
QT += multimediawidgets
