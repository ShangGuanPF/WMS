// -------------------------------------------------------------------------------------------------------------------
//
//  File: MinimapView.h
//
//  Copyright 2016 (c) Decawave Ltd, Dublin, Ireland.
//
//  All rights reserved.
//
//  Author:
//
// -------------------------------------------------------------------------------------------------------------------

#ifndef MINIMAPVIEW_H
#define MINIMAPVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>

class MinimapView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MinimapView(QWidget *parent = 0);

signals:

public slots:

protected slots:
    void onReady();
    void floorplanChanged();
    void visibleRectChanged();

protected:
    virtual void drawForeground(QPainter * painter, const QRectF & rect);
    virtual void resizeEvent(QResizeEvent *event);

    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void wheelEvent(QWheelEvent *event);

private:
    QGraphicsScene *_scene;
};

#endif // MINIMAPVIEW_H
