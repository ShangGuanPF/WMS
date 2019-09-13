// -------------------------------------------------------------------------------------------------------------------
//
//  File: RTLSClient.h
//
//  Copyright 2016 (c) Decawave Ltd, Dublin, Ireland.
//
//  All rights reserved.
//
//  Author:
//
// -------------------------------------------------------------------------------------------------------------------

#ifndef RTLSCLIENT_H
#define RTLSCLIENT_H

#include <QObject>

#include "SerialConnection.h"
#include "trilateration.h"
#include <stdint.h>

class QFile;
class DataAnchor;
class DataTag;

#include <armadillo>
using namespace arma;

#define PI (3.141592653589793)

#define MAX_NUM_ANCS_RNG 3 //A0-A1, A0-A2, A1-A2
#define ANC_RANGE_HIST 25
#define HIS_LENGTH 50
#define FILTER_SIZE 10  //NOTE: filter size needs to be > 2
#define FILTER_SIZE_SHORT 6

typedef struct
{
    double x_arr[HIS_LENGTH];
    double y_arr[HIS_LENGTH];
    double z_arr[HIS_LENGTH];
    double av_x, av_y, av_z; //average
    double fx, fy, fz; //filter average
    double sqx_arr[HIS_LENGTH]; //square x
    double sqy_arr[HIS_LENGTH];
    double sqz_arr[HIS_LENGTH];
    double avsq_x, avsq_y, avsq_z; //average of squares
    double errx_arr[HIS_LENGTH]; //error x (x-av_x)
    double erry_arr[HIS_LENGTH];
    double errz_arr[HIS_LENGTH];
    double averr_x, averr_y, averr_z; //avearge error
    double variancex, variancey, variancez;
    double std_x, std_y, std_z;
    double r95;
    int id;
    int arr_idx;
    int count;
    int numberOfLEs;
    int filterReady;
    bool ready;
    int rangeSeq;
    int rangeCount[256];
    int rangeValue[256][4]; //(mm) each tag ranges to 4 anchors - it has a range number which is modulo 256
} tag_reports_t;


#define MAX_NUM_TAGS (8)
#define MAX_NUM_ANCS (4)

typedef struct
{
    double x, y, z;
    uint64_t id;
    QString label;
    int tagRangeCorection[MAX_NUM_TAGS];
} anc_struct_t;

typedef struct
{
    double x, y, z;
    uint64_t id;
} pos_report_t;

typedef struct
{
  double x;
  double y;
} vec2d;

class RTLSClient : public QObject
{
    Q_OBJECT
public:
    explicit RTLSClient(QObject *parent = 0);

    int calculateTagLocation(vec3d *report, int count, int *ranges);
    void updateTagStatistics(int i, double x, double y, double z);
    void initialiseTagList(int id);
    double process_ma(double *array, int idx);
    double process_me(double *array, int idx);
    double process_avg(int idx);
    void setGWReady(bool set);
    void setUseAutoPos(bool useAutoPos);
    QStringList getLocationFilters(void);
    void setLocationFilter(int filter);
    void saveConfigFile(QString filename);
    void loadConfigFile(QString filename);

    int* getTagCorrections(int anchID);

    void addMissingAnchors(void);

    void trilaterateTag(int tid, int seq);
    void processTagRangeReport(int aid, int tid, int range, int lnum, int seq);
    void processAnchRangeReport(int aid, int tid, int range, int lnum, int seq);

    void mds(mat twrdistance, int nNodes, int viewNode, mat* transCoord);
    void angleRotation(mat transCoord, int nNodes, mat* estCoord);

    void openLogFile(QString userfilename);
    void closeLogFile(void);
    const QString &getLogFilePath();

signals:
    void anchPos(quint64 anchorId, double x, double y, double z,bool, bool);
    void tagPos(quint64 tagId, double x, double y, double z);
    void tagStats(quint64 tagId, double x, double y, double z, double r95);
    void tagRange(quint64 tagId, quint64 aId, double x);
    void statusBarMessage(QString status);

    void centerOnAnchors();
    void enableFiltering(void);
    void ancRanges(int a01, int a02, int a12);

protected slots:
    void onReady();
    void onConnected(QString ver, QString conf);

    void updateAnchorXYZ(int id, int x, double value);
    void updateTagCorrection(int aid, int tid, int value);

private slots:
    void newData();
    void connectionStateChanged(SerialConnection::ConnectionState);

private:
    bool _graphicsWidgetReady;
    bool _first;
    bool _useAutoPos;

    QList <tag_reports_t> _tagList;

    anc_struct_t _ancArray[MAX_NUM_ANCS];

    int _ancRangeCount;
    double _ancRangeArray[MAX_NUM_ANCS_RNG][ANC_RANGE_HIST]; //contains the last 50 ranges so we can calculate average

    double _ancRangeValues[MAX_NUM_ANCS][MAX_NUM_ANCS];
    double _ancRangeValuesAvg[MAX_NUM_ANCS][MAX_NUM_ANCS];

    QFile *_file;
    QFile *_fileDbg;

    QSerialPort *_serial;
    QStringList _locationFilterTypes ;
    int _usingFilter;
    uint8_t _ancRangeLastSeq;
    uint8_t _configuration;
    QString _version;
    QString _config;
    QString _logFilePath;

    int _filterSize;
};

void r95Sort(double s[], int l, int r);

#endif // RTLSCLIENT_H
