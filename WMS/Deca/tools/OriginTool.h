// -------------------------------------------------------------------------------------------------------------------
//
//  File: OriginTool.h
//
//  Copyright 2016 (c) Decawave Ltd, Dublin, Ireland.
//
//  All rights reserved.
//
//  Author:
//
// -------------------------------------------------------------------------------------------------------------------

#ifndef ORIGINTOOL_H
#define ORIGINTOOL_H

#include "AbstractTool.h"

/**
 * The OriginTool class is a tool used for setting the floorplan's origin point.
 *
 * It reacts to the clicked() event.
 * When clicked() is called, the origin is calculated based on the click position, and the tool finishes right away.
 * @see AbstractTool
 */
class OriginTool : public AbstractTool
{
    Q_OBJECT
public:
    explicit OriginTool(QObject *parent = 0);
    virtual ~OriginTool() {}

    virtual QCursor cursor();

    /**
     * Handle mouse clicks.
     * This function calculate the new origin point based on \a scenePos, and updates it with the new value.
     * The tool then emits the done() signal.
     *
     * @param scenePos the position of the click in scene coordinates.
     */
    virtual void clicked(const QPointF &scenePos);

signals:

public slots:

};

#endif // ORIGINTOOL_H
