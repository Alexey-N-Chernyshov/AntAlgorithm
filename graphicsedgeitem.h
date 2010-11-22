#ifndef GRAPHICSEDGEITEM_H
#define GRAPHICSEDGEITEM_H

#include <QGraphicsItem>

class GraphicsTextItem;
class GraphicsNodeItem;

class GraphicsEdgeItem : public QGraphicsItem
{
public:
    explicit GraphicsEdgeItem(GraphicsNodeItem *sourceNode, GraphicsNodeItem *destNode, QGraphicsItem *parent = 0);
    ~GraphicsEdgeItem();

    void setLowerValue(double val);
    void setShowLowerValue(bool val);

protected:
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    GraphicsNodeItem *source, *dest;
    GraphicsTextItem *upperTextItem;
    QGraphicsLineItem *line;

    double lowerValue;
    bool showLowerValue;
};

#endif // GRAPHICSEDGEITEM_H
