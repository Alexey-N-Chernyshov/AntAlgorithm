#ifndef GRAPHICSNODEITEM_H
#define GRAPHICSNODEITEM_H

#include <QGraphicsItem>

class GraphicsEdgeItem;

class GraphicsNodeItem : public QGraphicsItem
{
public:
    enum TypeNode{ StartNode, SimpleNode, EndNode };

    GraphicsNodeItem(QGraphicsItem *parent = 0);
    ~GraphicsNodeItem();

    void setTypeNode(TypeNode type);
    void addEdge(GraphicsEdgeItem *edge);
    void removeEdge(GraphicsEdgeItem *edge);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    QRectF boundingRect() const;
    QPainterPath shape() const;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    TypeNode m_type;
    QList<GraphicsEdgeItem *> edges;
};

#endif // GRAPHICSNODEITEM_H
