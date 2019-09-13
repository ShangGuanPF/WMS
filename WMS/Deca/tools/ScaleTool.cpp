// -------------------------------------------------------------------------------------------------------------------
//
//  File: ScaleTool.cpp
//
//  Copyright 2016 (c) Decawave Ltd, Dublin, Ireland.
//
//  All rights reserved.
//
//  Author:
//
// -------------------------------------------------------------------------------------------------------------------

#include "ScaleTool.h"

#include "RTLSDisplayApplication.h"
#include "mainwindow.h"
#include "ViewSettings.h"

#include <QCursor>
#include <QInputDialog>
#include <QPainter>
#include <QDebug>

ScaleTool::ScaleTool(Axis a, QObject *parent) :
    AbstractTool(parent),
    _axis(a),
    _state(FirstPoint)
{
}

QCursor ScaleTool::cursor()
{
    return Qt::CrossCursor;
}

void ScaleTool::draw(QPainter *painter, const QRectF &rect, const QPointF &cursor)
{
    Q_UNUSED(rect)

    if (_state == SecondPoint)
    {
        painter->save();
        painter->setPen(QPen(QBrush(Qt::black), 0));
        painter->drawLine(_first, cursor);
        painter->restore();
    }
}

void ScaleTool::clicked(const QPointF &scenePos)
{
    ViewSettings *vs = RTLSDisplayApplication::viewSettings();

    if (_state == FirstPoint)
    {
        _first = scenePos;
        _state = SecondPoint;
    }
    else if (_state == SecondPoint)
    {
        double p1 = (_axis == XAxis) ? _first.x() : _first.y();
        double p2 = (_axis == XAxis) ? scenePos.x() : scenePos.y();

        bool ok;
        double distance = QInputDialog::getDouble(RTLSDisplayApplication::mainWindow(), "Distance", "Distance between the two points", qAbs(p2 - p1), 0, 1000, 3, &ok);

        if (ok)
        {
            double r = qAbs(p2 - p1) / distance;
            if (_axis == XAxis)
                vs->setFloorplanXScale(r * vs->floorplanXScale());
            else
                vs->setFloorplanYScale(r * vs->floorplanYScale());
        }
        emit done();
    }
}

void ScaleTool::cancel()
{
    emit done(false);

    _first = QPointF();
    _state = FirstPoint;
}
