// -------------------------------------------------------------------------------------------------------------------
//
//  File: ScaleTool.h
//
//  Copyright 2016 (c) Decawave Ltd, Dublin, Ireland.
//
//  All rights reserved.
//
//  Author:
//
// -------------------------------------------------------------------------------------------------------------------

#ifndef SCALETOOL_H
#define SCALETOOL_H

#include "AbstractTool.h"

#include <QPointF>

/**
 * The ScaleTool class is a tool used to change the floorplan's scale.
 *
 * It allows the user to select two points by waiting for two consecutive clicked() events.
 * Once the user has clicked on two points, the tool shows a popup to enter the distance between the two points.
 * The scale is recalculated and stored.
 */
class ScaleTool : public AbstractTool
{
    Q_OBJECT
public:
    /**
     * The Axis enum indicates on what axis this tool operates.
     */
    enum Axis {
        XAxis, ///< Change the bitmap's X scale
        YAxis ///< Change the bitmap's Y scale
    };

    /**
     * Construct a new ScaleTool.
     * @param a axis on which the tool should operate.
     * @param parent parent object
     */
    explicit ScaleTool(Axis a, QObject *parent = 0);
    virtual ~ScaleTool() {}

    virtual QCursor cursor();

    /**
     * Draw the tool on the scene.
     * Once the first point is selected, this function draws a line between the first point and the cursor.
     * @param painter the painting context
     * @param rect the area which should be repainted
     * @param cursor the current position of the mouse, in scene coordinates
     */
    virtual void draw(QPainter *painter, const QRectF &rect, const QPointF &cursor);

    /**
     * Handle mouse clicks.
     *
     * The first time, it simply saves the point position for later, and moves on to the ScaleTool::SecondPoint state.
     *
     * On the second time, the previously stored point and the position of the new click is used to calculate the new scale.
     * @param scenePos the position of the click in scene coordinates.
     */
    virtual void clicked(const QPointF &scenePos);

public slots:
    virtual void cancel();

private:
    Axis _axis;

    QPointF _first;

    /**
     * Tool's possible states.
     */
    enum State {
        FirstPoint, ///< Waiting to select the first point.
        SecondPoint ///< Waiting to select the second point.
    };

    /**
     * The tool's current state.
     */
    State _state;
};

#endif // SCALETOOL_H
