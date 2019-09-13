// -------------------------------------------------------------------------------------------------------------------
//
//  File: RubberBandTool.h
//
//  Copyright 2016 (c) Decawave Ltd, Dublin, Ireland.
//
//  All rights reserved.
//
//  Author:
//
// -------------------------------------------------------------------------------------------------------------------

#ifndef RUBBERBANDTOOL_H
#define RUBBERBANDTOOL_H

#include "AbstractTool.h"

#include <QPointF>
#include <QSet>

class QGraphicsItem;

/**
 * The RubberBandTool class is a tool used to select anchors using a click and drag to draw a selection box.
 * Once the user has started the drag, a rectangular selection box is drawn, and all items within the box get selected. *
 *
 * In order to differentiate this tool's click and drag with the one used to move the scene,
 * the tool is started if the Control button is held during the initial mouse press event.
 * This is handled by the GraphicsView::mousePressEvent(), and is outside the scope of this class.
 */
class RubberBandTool : public AbstractTool
{
    Q_OBJECT
public:
    explicit RubberBandTool(QObject *parent = 0);
    virtual ~RubberBandTool() {}

    /**
     * Draw the tool on the scene.
     * It draws a rectangular box between the start point, and the current mouse position.
     *
     * @param painter the painting context
     * @param rect the area which should be repainted
     * @param cursor the current position of the mouse, in scene coordinates
     */
    virtual void draw(QPainter *painter, const QRectF &rect, const QPointF &cursor);

    /**
     * Handle mouse press events.
     * The tool stores the position of the press as the start point of the selection, and returns true in order to receive subsequent events.
     * @param scenePos the event's position, in scene coordinates
     * @return true
     */
    virtual bool mousePressEvent(const QPointF &scenePos);

    /**
     * Handle mouse move events.
     * This function updates the selection model based on the rectangular region formed between the start point and the current point.
     *
     * @param scenePos the event's position, in scene coordinates
     */
    virtual void mouseMoveEvent(const QPointF &scenePos);

    /**
     Handle mouse release events.
     This function simply emits the done() signal to signify the selection processs is complete.

     * @param scenePos the event's position, in scene coordinates
     */
    virtual void mouseReleaseEvent(const QPointF &scenePos);

signals:

public slots:
    virtual void cancel();

private:
    QPointF _start;
    QSet<QGraphicsItem *> _previousItems;
};

#endif // RUBBERBANDTOOL_H
