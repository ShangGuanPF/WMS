// -------------------------------------------------------------------------------------------------------------------
//
//  File: GraphicsWidget.h
//
//  Copyright 2016 (c) Decawave Ltd, Dublin, Ireland.
//
//  All rights reserved.
//
//  Author:
//
// -------------------------------------------------------------------------------------------------------------------

#ifndef GRAPHICSWIDGET_H
#define GRAPHICSWIDGET_H

#include <QGraphicsRectItem>
#include <QWidget>
#include <QAbstractItemView>
#include <QGraphicsView>
#include "RTLSClient.h"
#include <QTableView>
#include <QSqlTableModel>
#include <QTableWidget>
#include <QSerialPort>
#include "storage.h"

#include <QtMultimedia/QCamera>

#include <QtMultimedia/QCameraInfo>
#include <QCameraViewfinder>
#include <QtMultimedia/QCameraImageCapture>
#include <QFileDialog>
#include <QDebug>
#include "GraphicsWidget.h"

namespace Ui {
class GraphicsWidget;
}

class GraphicsDataModel;
class QGraphicsScene;
class QModelIndex;
class GraphicsView;
class QAbstractGraphicsShapeItem;
class QGraphicsItem;

struct Tag
{
    Tag(void)
    {
        idx = 0;
        ridx = 0;
    }

    quint64 id;
    int idx;
    int ridx;
    QVector<QAbstractGraphicsShapeItem *> p;
    QAbstractGraphicsShapeItem *avgp;
    QAbstractGraphicsShapeItem *r95p;   //r95 circle around the average point, average of 100
    QAbstractGraphicsShapeItem *geop;   //geofencing circle around the (geofencing) anchor

    QAbstractGraphicsShapeItem *postion_tag;//用来跟踪tag
    bool r95Show;

    double tsPrev; //previous timestamp in sec
    double colourH;
    double colourS;
    double colourV;

    bool showLabel;
    QGraphicsSimpleTextItem *tagLabel;
    QString tagLabelStr;
};

struct Anchor
{
    Anchor(void)
    {
        idx = 0;
        ridx = 0;
    }
    quint64 id;
    int idx;
    int ridx;
    bool show;
    QAbstractGraphicsShapeItem * a;
    QGraphicsSimpleTextItem *ancLabel;

    QPointF p;
};

class GraphicsWidget : public QWidget
{
    Q_OBJECT

public:

    bool find_tag_flag=false;

    QSqlTableModel *model;
    QSqlTableModel *model1;
    QSqlTableModel *model2;
    QSqlTableModel *model3;

    QSqlTableModel *model5;

    float page0;
    float page1;
    float page2;
    float page3;

    enum Column {
        ColumnID = 0,   ///< 64 bit address of the anchor (uint64)
        ColumnX,        ///< X coordinate (double)
        ColumnY,        ///< Y coordinate (double)
        ColumnZ,        ///< Z coordinate (double)
       // ColumnBlinkRx,   ///< % of received blinks
       // ColumnLocations, ///< % of successful multilaterations
        ColumnR95,       ///< R95
        ColumnRA0,
        ColumnRA1,
        ColumnRA2,
        ColumnRA3,
        ColumnIDr,       ///< ID raw (hex) hidden
        ColumnCount
    };

    explicit GraphicsWidget(QWidget *parent = 0);
    ~GraphicsWidget();

    GraphicsView *graphicsView();

    int findTagRowIndex(QString &t);
    void insertTag(int ridx, QString &t, bool showR95, bool showLabel, QString &l);
    void tagIDToString(quint64 tagId, QString *t);
    void addNewTag(quint64 tagId);
    void addNewAnchor(quint64 ancId, bool show);
    void insertAnchor(int ridx, double x, double y, double z, int *array, bool show);
    void loadConfigFile(QString filename);
    void saveConfigFile(QString filename);

    void hideTACorrectionTable(bool hidden);

    void compare(QString,QString);


    void outputQtableviewtoexcel(QTableView *table,QString title);//导出excel表格
    void outputQtablewidgettoexcel(QTableWidget *table,QString title);

    static QSerialPort *Serial;
    static bool serial_flag;





signals:
    void updateAnchorXYZ(int id, int x, double value);
    void updateTagCorrection(int aid, int tid, int value);
    void centerAt(double x, double y);
    void centerRect(const QRectF &visibleRect);

    void setTagHistory(int h);
    void sendOrderValue(QString);
    void sendStaffID(QString);
    void sendStoreID(QString);
    void sendProductID(QString);

    void sendsetting();



public slots:

    void centerOnAnchors(void);
    void anchTableEditing(bool);

    void tagPos(quint64 tagId, double x, double y, double z);
    void tagStats(quint64 tagId, double x, double y, double z, double r95);
    void tagRange(quint64 tagId, quint64 aId, double range);

    void anchPos(quint64 anchId, double x, double y, double z, bool show, bool updatetable);

    void tagTableChanged(int r, int c);
    void anchorTableChanged(int r, int c);
    void tagTableClicked(int r, int c);
    void anchorTableClicked(int r, int c);
    void itemSelectionChanged(void);
    void itemSelectionChangedAnc(void);
    void clearTags(void);

    void setShowTagHistory(bool);
    void setShowTagAncTable(bool anchorTable, bool tagTable, bool ancTagCorr);
    void showGeoFencingMode(bool set);
    void zone1Value(double value);
    void zone2Value(double value);
    void tagHistoryNumber(int value);
    void zone(int zone, double radius, bool red);
    void setAlarm(bool in, bool out);

    void ancRanges(int a01, int a02, int a12);

    //出库管理
    void outstore_management(int num);
    void outstore_management2(int num);


protected slots:
    void onReady();

protected:
    void tagHistory(quint64 tagId);

private slots:
   // void on_graphicsView_rubberBandChanged(const QRect &viewportRect, const QPointF &fromScenePoint, const QPointF &toScenePoint);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    //void on_toolBox_2_destroyed();

   // void on_pushButton_6_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_22_clicked();

    void on_pushButton_15_clicked();

   // void on_pushButton_15_clicked(bool checked);

    void on_pushButton_23_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_21_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_19_clicked();

    void on_pushButton_24_clicked();

    void on_pushButton_25_clicked();

    void on_pushButton_27_clicked();

   // void on_pushButton_28_clicked();

    void on_pushButton_31_clicked();

    void on_pushButton_26_clicked();

    void on_pushButton_29_clicked();

    void on_pushButton_36_clicked();

    void on_pushButton_38_clicked();

   // void on_pushButton_39_clicked();

    void on_pushButton_30_clicked();

    void on_pushButton_37_clicked();

    void on_pushButton_48_clicked();

    void on_pushButton_49_clicked();

    void on_pushButton_43_clicked();

    void on_pushButton_41_clicked();
    void on_pushButton_45_clicked();

    void on_pushButton_44_clicked();

    void on_pushButton_46_clicked();

    void on_pushButton_40_clicked();

    void on_pushButton_14_clicked();

   // void on_comboBox_activated(const QString &arg1);

   // void on_toolBox_destroyed();

  //  void trans_serialdata();

    void on_pushButton_50_clicked();

    void on_pushButton_56_clicked();

    void on_pushButton_61_clicked();

   // void on_pushButton_62_clicked();

    void on_pushButton_52_clicked();

    void on_pushButton_57_clicked();

    void on_pushButton_63_clicked();

    void on_pushButton_53_clicked();

    void on_pushButton_58_clicked();

    void on_pushButton_54_clicked();

    void on_pushButton_59_clicked();

    void on_pushButton_64_clicked();

    void on_pushButton_55_clicked();

    void on_pushButton_60_clicked();

    void on_pushButton_65_clicked();

    void on_toolButton_clicked();

    void on_toolButton_2_clicked();

    void on_toolButton_3_clicked();

    void on_toolButton_5_clicked();

    void on_toolButton_4_clicked();

    void on_toolButton_6_clicked();

    void on_toolButton_9_clicked();

    void on_toolButton_7_clicked();

    void on_toolButton_8_clicked();

    void on_pushButton_51_clicked();

    void on_pushButton_42_clicked();

    void on_pushButton_66_clicked();

    void on_pushButton_72_clicked();

    void on_pushButton_73_clicked();

   // void on_pushButton_74_clicked();

    void on_pushButton_75_clicked();

    void on_pushButton_67_clicked();

    void on_pushButton_69_clicked();

    void on_pushButton_68_clicked();

    void on_pushButton_34_clicked();

    void on_pushButton_33_clicked();

    void on_toolButton_11_clicked();

    void on_pushButton_32_clicked();

    void on_pushButton_76_clicked();

    void stocking_1(int num);
     void stocking_2(int num);


     void on_toolButton_10_clicked();

     void on_toolButton_12_clicked();

     void on_pushButton_28_clicked();

     void on_pushButton_78_clicked();

     void on_pushButton_74_clicked();

     void on_pushButton_77_clicked();

     void on_pushButton_82_clicked();

    // void on_pushButton_82_released();

     void on_pushButton_86_clicked();
     void display(QString store_name);

     void on_pushButton_101_clicked();

     void on_pushButton_102_clicked();
    // void display_biaoshidata();

     void on_takephoto_clicked();

     void on_pushButton_103_clicked();

     void on_pushButton_91_clicked();

     void on_pushButton_92_clicked();

     void on_pushButton_100_clicked();

     void on_pushButton_95_clicked();

     void on_pushButton_39_clicked();

signals:
    void sendOrderID(QString,QString); //标识管理中 新增标签 给 tag_add 发送编号、和标识
    //toolbox发送index给tabwidget
    void send_click0(int);
    void send_click(int);
    void send_click2(int);
    void send_click3(int);
    void send_click4(int);
    void send_click5(int);
    void send_click6(int);
    void send_click7(int);
    void send_click8(int);
    void send_click9(int);
    void send_click_10(int);
    void send_num(QString);

    void show_history(QString);//显示历史轨迹
    void unshow_history();//取消显示历史轨迹

private:
    Ui::GraphicsWidget *ui;
    QGraphicsScene *_scene;

    QMap<quint64, Tag*> _tags;
    QMap<quint64, Anchor *> _anchors;
    QMap<quint64, QString> _tagLabels;
    float _tagSize;
    int   _historyLength;
    bool _showHistory;
    bool _showHistoryP;
    bool _busy;
    bool _ignore;
    bool _geoFencingMode;
    bool _alarmOut;

    int _selectedTagIdx;

    QAbstractGraphicsShapeItem *zone1;
    QAbstractGraphicsShapeItem *zone2;

    double _zone1Rad;
    double _zone2Rad;
    double _maxRad;
    double _minRad;
    bool _zone1Red;
    bool _zone2Red;


    QGraphicsLineItem * _line01;
    QGraphicsLineItem * _line02;
    QGraphicsLineItem * _line12;

    QMap<QString, int>::iterator order_itera;
    QMap<QString, int> order_num_map;
    QVector<QString>   order_id;
    void empytOrdermap();

    /*

    不同形式的query表的声明
    */
      QSqlTableModel *model_staff;
      QSqlTableModel *model_product;
      QSqlTableModel *model_store;
      QSqlQueryModel *model_staffquery;
      QSqlQueryModel *model_productquery;
      QSqlQueryModel *model_storequery;
      QSqlQueryModel *model_storagequery;

      QSqlQueryModel *model_staffquery0;//用于查询表的总行数
      QSqlQueryModel *model_productquery0;
      QSqlQueryModel *model_storequery0;
      QSqlQueryModel *model_storagequery0;

   /*
    * 员工表，产品信息表，仓库表
    */
      QString MODEL_STAFF = "staff_management";
      QString MODEL_PRODUCT = "product_imformation";
      QString MODEL_STORE = "stores_management";
      QString MODEL_STORAGE = "storage_copy";

     /*
      * 全局变量各个表的总行数，总页数
      */
      float staff_totalline,store_totalline,product_totalline,storage_totalline;
      int staff_totalpage,store_totalpage,product_totalpage,storage_totalpage;



      //摄像头部分

      QCameraViewfinder *viewfinder;
      QCameraImageCapture *imageCapture;
       QCamera *m_Cam;


};
#endif // GRAPHICSWIDGET_H








