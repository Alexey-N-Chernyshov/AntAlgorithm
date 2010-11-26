#ifndef GRAPHICSEDGEITEM_H
#define GRAPHICSEDGEITEM_H

#include <QGraphicsItem>

class GraphicsTextItem;
class GraphicsNodeItem;

class GraphicsEdgeItem : public QGraphicsItem
{
public:
    enum { Type = UserType + 10 };
    explicit GraphicsEdgeItem(GraphicsNodeItem *sourceNode, GraphicsNodeItem *destNode, QGraphicsItem *parent = 0);
    ~GraphicsEdgeItem();

    int type() const;
    void setColor(QColor color);
    void setLowerValue(double val);
    void setShowLowerValue(bool val);
    GraphicsNodeItem *getSourceNode() const;
    GraphicsNodeItem *getDestinationNode() const;
    float getWeight() const;

protected:
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    GraphicsNodeItem *source, *dest;
    GraphicsTextItem *upperTextItem;
    QGraphicsLineItem *line;
    QColor m_color;
    double lowerValue;
    bool showLowerValue;
};

#endif // GRAPHICSEDGEITEM_H
