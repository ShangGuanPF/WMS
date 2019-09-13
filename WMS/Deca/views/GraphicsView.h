// -------------------------------------------------------------------------------------------------------------------
//
//  File: GraphicsView.h
//
//  Copyright 2016 (c) Decawave Ltd, Dublin, Ireland.
//
//  All rights reserved.
//
//  Author:
//
// -------------------------------------------------------------------------------------------------------------------

#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>

class QGestureEvent;
class AbstractTool;

/**
 * The GraphicsView class draws the scene and provides user interaction using the mouse.
 *
 * @par User Interaction
 * @parblock
 * User interaction is quite tricky as we have to handle many different interaction based on very little mouse events.
 * - Scene interaction (Selecting anchors, mvoing them, ...) - This is handled by QGraphicsScene and GraphicsDataItem.
 * - Unselecting all anchors by clicking on the background.
 * - Zooming using the scroll wheel
 * - Panning by dragging
 * - Contextual menu by right-click
 * - Canceling the current tool by right-click
 * - Starting a RubberBandTool on Ctrl+Drag
 * - Tools listening to AbstractTool::clicked() events
 * - Tools listening to AbstractTool::mousePressEvent() events
 *
 * Most of them are handled by the mousePressEvent()/mouseMoveEvent()/mouseReleaseEvent() cycle.
 *
 * During mousePressEvent(), we find the suited action, and decide of a MouseContext based on that.
 * The MouseContext is kept until mouseReleaseEvent()
 * @endparblock
 *
 * @par Visible Rectangle
 * @parblock
 * The GraphicsView keeps track of the visible rectangle, in scene coordinates. This rectangle will always be visible on the screen.
 * Initially, the visible rectangle is the square from (0,0) to (1, 1) \n
 * The visible rectangle can be transformed using translateView() or scaleView() or changed using setVisibleRect().
 * Whenever the visible rectangle changes, for any reason, the visibleRectChanged() signal is called.
 * @endparblock
 *
 * @par Tool
 * Tools allow simple interaction inside the scene. A new tool can be set using setTool(). The tool then remains active until it's AbstractTool::done() signal is emitted. \n
 * When ESC button or right click is pressed, the view attempts to cancel the tool by calling AbstractTool::cancel().
 * @see AbstractTool
 */
class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GraphicsView(QWidget *parent = 0);
    virtual ~GraphicsView();

    /**
     * Translate the visible rectangle by (\a dx, \a dy) in screen coordinates.
     * @param dx X offset
     * @param dy Y offset
     */
    void translateView(qreal dx, qreal dy);

    /**
     * Scale the visible rectangle by (\a sx, \a sy).
     * The center of the rectangle stays fixed.
     * @param sx X scaling factor
     * @param sy Y scaling factor
     */
    void scaleView(qreal sx, qreal sy);

    /**
     * Scale the visible rectangle by (\a sx, \a sy), leaving the point at coordinates \a center unmoved on the screen.
     * @param sx X scaling factor
     * @param sy Y scaling factor
     * @param center Center of the tranformation
     */
    void scaleView(qreal sx, qreal sy, QPointF center);

    /**
     * Changes the current visible rectangle.
     * @param visibleRect the new visible rectangle
     */
    void setVisibleRect(const QRectF &visibleRect);

    /**
     * @return the current visible rectangle
     */
    QRectF visibleRect() const;

    /**
     * Assigns a new tool instance to this view.
     * If \a tool is NULL, it removes any previous tool.
     * @param tool the new tool.
     */
    void setTool(AbstractTool *tool);

signals:
    /**
     * visibleRectChanged is emitted whenever the visible rectangle is changed.
     * @param rect the new visible rectangle.
     */
    void visibleRectChanged(const QRectF &rect);

protected slots:
    void onReady();

    void floorplanChanged();

    void toolDone();
    void toolDestroyed();

    void centerRect(const QRectF &visibleRect);
    void centerAt(double x, double y);

protected:
    virtual void showEvent(QShowEvent *event);
    virtual void resizeEvent(QResizeEvent *event);
    virtual void wheelEvent(QWheelEvent *event);

    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

    virtual void contextMenuEvent(QContextMenuEvent *event);

    virtual void keyPressEvent(QKeyEvent *event);

    void drawGrid(QPainter *painter, const QRectF &rect);
    void drawOrigin(QPainter *painter);
    void drawFloorplan(QPainter *painter, const QRectF &rect);
    virtual void drawForeground(QPainter *painter, const QRectF &rect);
    virtual void drawBackground(QPainter *painter, const QRectF &rect);

private:
    QPoint _lastMouse;

    QRectF _visibleRect;

    AbstractTool *_tool;

    bool _ignoreContextMenu;

    /**
     * @brief The MouseContext enum represents the possible states of mouse interaction.
     * Depending on the context, the mouse events will be handled differently.
     */
    enum MouseContext {
        DefaultMouseContext, ///< All simple interactions
        PanningMouseContext, ///< Panning around by dragging
        SceneMouseContext, ///< Mouse events are handled by the scene and GraphicsDataItem
        ToolMouseContext ///< Tool receives the mouse events using the "complex" events mechanism. @see AbstractTool
    };
    MouseContext _mouseContext;
};

#endif // GRAPHICSVIEW_H
