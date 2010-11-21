#ifndef GRAPHICSNODEITEM_H
#define GRAPHICSNODEITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include <QRectF>
#include <QStyleOptionGraphicsItem>

class GraphicsNodeItem : public QGraphicsItem
{
public:
    enum TypeNode{ StartNode, SimpleNode, EndNode };

    GraphicsNodeItem(QGraphicsItem *parent = 0);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void setType(TypeNode type);
    int getType() const;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    TypeNode m_type;

signals:

public slots:

};

#endif // GRAPHICSNODEITEM_H
