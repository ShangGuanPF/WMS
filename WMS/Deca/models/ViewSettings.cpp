// -------------------------------------------------------------------------------------------------------------------
//
//  File: ViewSettings.cpp
//
//  Copyright 2016 (c) Decawave Ltd, Dublin, Ireland.
//
//  All rights reserved.
//
//  Author:
//
// -------------------------------------------------------------------------------------------------------------------

#include "ViewSettings.h"

ViewSettings::ViewSettings(QObject *parent)
    : QObject(parent),
      _gridWidth(0.5),
      _gridHeight(0.5),
      _floorplanFlipX(false),
      _floorplanFlipY(false),
      _floorplanXScale(100),
      _floorplanYScale(100),
      _floorplanXOffset(0),
      _floorplanYOffset(0),
      _showOrigin(true),
      _showGrid(true),
      _floorplanPath(""),
      _floorplanShow(false)
{
    QObject::connect(this, SIGNAL(gridWidthChanged(double)), this, SLOT(viewSettingsChanged()));
    QObject::connect(this, SIGNAL(gridHeightChanged(double)), this, SLOT(viewSettingsChanged()));

    QObject::connect(this, SIGNAL(floorplanFlipXChanged(bool)), this, SLOT(viewSettingsChanged()));
    QObject::connect(this, SIGNAL(floorplanFlipYChanged(bool)), this, SLOT(viewSettingsChanged()));

    QObject::connect(this, SIGNAL(floorplanXScaleChanged(double)), this, SLOT(viewSettingsChanged()));
    QObject::connect(this, SIGNAL(floorplanYScaleChanged(double)), this, SLOT(viewSettingsChanged()));

    QObject::connect(this, SIGNAL(showGridChanged(bool)), this, SLOT(viewSettingsChanged()));
    QObject::connect(this, SIGNAL(showOriginChanged(bool)), this, SLOT(viewSettingsChanged()));

    QObject::connect(this, SIGNAL(floorplanXOffsetChanged(double)), this, SLOT(viewSettingsChanged()));
    QObject::connect(this, SIGNAL(floorplanYOffsetChanged(double)), this, SLOT(viewSettingsChanged()));

    QObject::connect(this, SIGNAL(floorplanPixmapChanged()), this, SLOT(viewSettingsChanged()));
}

bool ViewSettings::originShow()
{
    return _showOrigin;
}

bool ViewSettings::gridShow()
{
    return _showGrid;
}

void ViewSettings::setSaveFP(bool set)
{
    _floorplanSave = set;

    emit showSave(_floorplanSave);
}

void ViewSettings::setShowOrigin(bool set)
{
    _showOrigin = set;

    emit showGO(_showOrigin, _showGrid);
}

void ViewSettings::setShowGrid(bool set)
{
    _showGrid = set;

    emit showGO(_showOrigin, _showGrid);
    emit floorplanChanged();
}

double ViewSettings::gridHeight() const
{
    return _gridHeight;
}

double ViewSettings::gridWidth() const
{
    return _gridWidth;
}

bool ViewSettings::floorplanFlipX() const
{
    return _floorplanFlipX;
}

bool ViewSettings::floorplanFlipY() const
{
    return _floorplanFlipY;
}

double ViewSettings::floorplanXScale() const
{
    return _floorplanXScale;
}

double ViewSettings::floorplanYScale() const
{
    return _floorplanYScale;
}

double ViewSettings::floorplanXOffset() const
{
    return _floorplanXOffset;
}

double ViewSettings::floorplanYOffset() const
{
    return _floorplanYOffset;
}

const QPixmap &ViewSettings::floorplanPixmap() const
{
    return _floorplanPixmap;
}

const QString &ViewSettings::getFloorplanPath()
{
    return _floorplanPath;
}

bool ViewSettings::floorplanSave() const
{
    return _floorplanSave;
}

QTransform ViewSettings::floorplanTransform() const
{
    return _floorplanTransform;
}

void ViewSettings::setGridWidth(double arg)
{
    if (_gridWidth != arg) {
        _gridWidth = arg;
        emit gridWidthChanged(arg);
    }
}

void ViewSettings::setGridHeight(double arg)
{
    if (_gridHeight != arg) {
        _gridHeight = arg;
        emit gridHeightChanged(arg);
    }
}

void ViewSettings::floorplanFlipX(bool arg)
{
    if (_floorplanFlipX != arg) {
        _floorplanFlipX = arg;
        emit floorplanFlipXChanged(arg);
    }
}

void ViewSettings::floorplanFlipY(bool arg)
{
    if (_floorplanFlipY != arg) {
        _floorplanFlipY = arg;
        emit floorplanFlipYChanged(arg);
    }
}

void ViewSettings::setFloorplanXScale(double arg)
{
    if (_floorplanXScale != arg) {
        _floorplanXScale = arg;
        emit floorplanXScaleChanged(arg);
    }
}

void ViewSettings::setFloorplanYScale(double arg)
{
    if (_floorplanYScale != arg) {
        _floorplanYScale = arg;
        emit floorplanYScaleChanged(arg);
    }
}

void ViewSettings::setFloorplanXOffset(double arg)
{
    if (_floorplanXOffset != arg) {
        _floorplanXOffset = arg;
        emit floorplanXOffsetChanged(arg);
    }
}

void ViewSettings::setFloorplanYOffset(double arg)
{
    if (_floorplanYOffset != arg) {
        _floorplanYOffset = arg;
        emit floorplanYOffsetChanged(arg);
    }
}

void ViewSettings::setFloorplanPixmap(const QPixmap &arg)
{
    _floorplanPixmap = arg;
    floorplanFlipX(true);
    emit floorplanPixmapChanged();
}

void ViewSettings::setFloorplanPath(const QString &arg)
{
    _floorplanPath = arg;
}

void ViewSettings::setFloorplanPathN(void)
{
    if (!_floorplanPath.isNull())
    {
        _floorplanShow = true;
        emit setFloorPlanPic();
    }
}

void ViewSettings::viewSettingsChanged()
{
    QTransform t;
    double xscale = floorplanXScale();
    double yscale = floorplanYScale();
    double xoffset = floorplanXOffset();
    double yoffset = floorplanYOffset();

    if (!floorplanPixmap().isNull() && (xscale != 0) && (yscale != 0))
    {
        if (floorplanFlipX())
        {
            t.scale(1, -1);
        }
        if (floorplanFlipY())
        {
            t.scale(-1, 1);
        }

        t.scale(1. / xscale, 1. / yscale);
        t.translate(-xoffset, -yoffset);
    }

    _floorplanTransform = t;
    emit floorplanChanged();
}

void ViewSettings::clearSettings(void)
{
    _floorplanXScale = 0;
    _floorplanYScale = 0;
    _floorplanXOffset = 0;
    _floorplanYOffset = 0;
    _floorplanFlipX = false;
    _floorplanFlipY = false;
}

void ViewSettings::floorplanShow(bool show)
{
    _floorplanShow = show;
    emit floorplanChanged();
}

bool ViewSettings::getFloorplanShow(void)
{
    return _floorplanShow;
}
