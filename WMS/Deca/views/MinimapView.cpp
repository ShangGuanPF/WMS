// -------------------------------------------------------------------------------------------------------------------
//
//  File: MinimapView.cpp
//
//  Copyright 2016 (c) Decawave Ltd, Dublin, Ireland.
//
//  All rights reserved.
//
//  Author:
//
// -------------------------------------------------------------------------------------------------------------------

#include "MinimapView.h"

#include "RTLSDisplayApplication.h"
#include "ViewSettings.h"
#include "GraphicsView.h"

#include <QMouseEvent>
#include <qmath.h>

MinimapView::MinimapView(QWidget *parent) :
    QGraphicsView(parent),
    _scene(new QGraphicsScene(this))
{
    setScene(_scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setDragMode(QGraphicsView::NoDrag);

    scale(1, -1);

    RTLSDisplayApplication::connectReady(this, "onReady()");
}

void MinimapView::onReady()
{
    QObject::connect(RTLSDisplayApplication::viewSettings(), SIGNAL(floorplanChanged()), this, SLOT(floorplanChanged()));
    QObject::connect(RTLSDisplayApplication::graphicsView(), SIGNAL(visibleRectChanged(QRectF)), this, SLOT(visibleRectChanged()));
}

void MinimapView::floorplanChanged()
{
    ViewSettings *vs = RTLSDisplayApplication::viewSettings();
    QRectF sceneRect = vs->floorplanTransform().map(QRectF(0, 0, vs->floorplanPixmap().width(), vs->floorplanPixmap().height())).boundingRect();

    _scene->setSceneRect(sceneRect);
    this->fitInView(sceneRect, Qt::KeepAspectRatio);
}

void MinimapView::visibleRectChanged()
{
    _scene->update();
}

void MinimapView::drawForeground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect)
    const QPixmap &pm = RTLSDisplayApplication::viewSettings()->floorplanPixmap();
    if (!pm.isNull())
    {
        painter->save();
        painter->setTransform(RTLSDisplayApplication::viewSettings()->floorplanTransform(), true);
        painter->setPen(QPen(QBrush(Qt::black), 1));
        painter->drawPixmap(0, 0, pm);
        painter->restore();

        painter->setPen(QPen(QBrush(Qt::red), 0.1));
        painter->drawRect(RTLSDisplayApplication::graphicsView()->visibleRect());
    }
}

void MinimapView::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
    ViewSettings *vs = RTLSDisplayApplication::viewSettings();
    QRectF sceneRect = vs->floorplanTransform().map(QRectF(0, 0, vs->floorplanPixmap().width(), vs->floorplanPixmap().height())).boundingRect();
    this->fitInView(sceneRect, Qt::KeepAspectRatio);
}

void MinimapView::mousePressEvent(QMouseEvent *event)
{
    QRectF visibleRect = RTLSDisplayApplication::graphicsView()->visibleRect();
    visibleRect.moveCenter(mapToScene(event->pos()));
    RTLSDisplayApplication::graphicsView()->setVisibleRect(visibleRect);
}

void MinimapView::mouseMoveEvent(QMouseEvent *event)
{
    QRectF visibleRect = RTLSDisplayApplication::graphicsView()->visibleRect();
    visibleRect.moveCenter(mapToScene(event->pos()));
    RTLSDisplayApplication::graphicsView()->setVisibleRect(visibleRect);
}

void MinimapView::wheelEvent(QWheelEvent *event)
{
    qreal s = pow((double)2, event->delta() / 360.0);
    RTLSDisplayApplication::graphicsView()->scaleView(s, s);
}
