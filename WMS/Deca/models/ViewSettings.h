// -------------------------------------------------------------------------------------------------------------------
//
//  File: ViewSettings.h
//
//  Copyright 2016 (c) Decawave Ltd, Dublin, Ireland.
//
//  All rights reserved.
//
//  Author:
//
// -------------------------------------------------------------------------------------------------------------------

#ifndef VIEWSETTINGS_H
#define VIEWSETTINGS_H

#include <QObject>
#include <QDebug>
#include <QPixmap>

/**
 * The ViewSettings class holds many properties about the view, such as the grid and viewplan settings.
 *
 * It uses Qt' property system, and can be accessed using a QPropertyModel.
 */
class ViewSettings : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double gridWidth READ gridWidth WRITE setGridWidth NOTIFY gridWidthChanged)
    Q_PROPERTY(double gridHeight READ gridHeight WRITE setGridHeight NOTIFY gridHeightChanged)
    Q_PROPERTY(bool floorplanFlipX READ floorplanFlipX WRITE floorplanFlipX NOTIFY floorplanFlipXChanged)
    Q_PROPERTY(bool floorplanFlipY READ floorplanFlipY WRITE floorplanFlipY NOTIFY floorplanFlipYChanged)
    Q_PROPERTY(double floorplanXScale READ floorplanXScale WRITE setFloorplanXScale NOTIFY floorplanXScaleChanged)
    Q_PROPERTY(double floorplanYScale READ floorplanYScale WRITE setFloorplanYScale NOTIFY floorplanYScaleChanged)
    Q_PROPERTY(double floorplanXOffset READ floorplanXOffset WRITE setFloorplanXOffset NOTIFY floorplanXOffsetChanged)
    Q_PROPERTY(double floorplanYOffset READ floorplanYOffset WRITE setFloorplanYOffset NOTIFY floorplanYOffsetChanged)
    Q_PROPERTY(bool showGrid READ gridShow WRITE setShowGrid NOTIFY showGridChanged)
    Q_PROPERTY(bool showOrigin READ originShow WRITE setShowOrigin NOTIFY showOriginChanged)
    Q_PROPERTY(QPixmap floorplanPixmap READ floorplanPixmap WRITE setFloorplanPixmap NOTIFY floorplanPixmapChanged)

    Q_PROPERTY(QTransform floorplanTransform READ floorplanTransform)

public:
    ViewSettings(QObject *parent = 0);

    double gridWidth() const;
    double gridHeight() const;

    bool floorplanSave() const;

    bool floorplanFlipX() const;
    bool floorplanFlipY() const;

    double floorplanXScale() const;
    double floorplanYScale() const;

    double floorplanXOffset() const;
    double floorplanYOffset() const;

    const QPixmap &floorplanPixmap() const;

    QTransform floorplanTransform() const;

    void clearSettings(void);
    void floorplanShow(bool);
    bool getFloorplanShow(void);
    //void floorplanFill(void);
    void setFloorplanPath(const QString &arg);
    void setFloorplanPathN(void);
    const QString &getFloorplanPath();

    bool gridShow();
    bool originShow();

public slots:
    void setGridWidth(double arg);
    void setGridHeight(double arg);

    void floorplanFlipX(bool arg);
    void floorplanFlipY(bool arg);

    void setFloorplanXScale(double arg);
    void setFloorplanYScale(double arg);

    void setFloorplanXOffset(double arg);
    void setFloorplanYOffset(double arg);

    void setFloorplanPixmap(const QPixmap &arg);

    void setShowGrid(bool);
    void setShowOrigin(bool);

    void setSaveFP(bool);

signals:
    void gridWidthChanged(double arg);
    void gridHeightChanged(double arg);

    void floorplanFlipXChanged(bool arg);
    void floorplanFlipYChanged(bool arg);

    void floorplanXScaleChanged(double arg);
    void floorplanYScaleChanged(double arg);

    void floorplanXOffsetChanged(double arg);
    void floorplanYOffsetChanged(double arg);

    void showGridChanged(bool arg);
    void showOriginChanged(bool arg);

    void floorplanPixmapChanged();

    void floorplanChanged();

    void showGO(bool, bool);
    void showSave(bool);

    void setFloorPlanPic();

private slots:
    void viewSettingsChanged();

private:
    double _gridWidth;
    double _gridHeight;
    bool _floorplanFlipX;
    bool _floorplanFlipY;
    double _floorplanXScale;
    double _floorplanYScale;
    double _floorplanXOffset;
    double _floorplanYOffset;
    bool _showOrigin;
    bool _showGrid;
    bool _floorplanSave;
    QPixmap _floorplanPixmap;
    QString _floorplanPath;
    bool _floorplanShow;
    QTransform _floorplanTransform;
};

#endif // VIEWSETTINGS_H
