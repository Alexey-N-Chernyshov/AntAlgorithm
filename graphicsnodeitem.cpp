#include "graphicsnodeitem.h"

GraphicsNodeItem::GraphicsNodeItem(QGraphicsItem *parent) :
        QGraphicsItem(parent),
        m_type(SimpleNode)
{
    setFlags(ItemIsSelectable | ItemIsMovable);
    setZValue(-1);
}

void GraphicsNodeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::lightGray);
    painter->drawEllipse(-6, -7, 16, 16);

    QRadialGradient gradient(-3, -3, 7);
    if (option->state & QStyle::State_Sunken) {
        gradient.setColorAt(0, QColor(Qt::white));
        gradient.setColorAt(1, QColor(Qt::darkGray));
    } else {
        gradient.setColorAt(0, Qt::white);
        gradient.setColorAt(1, Qt::black);
    }
    painter->setBrush(gradient);
    painter->drawEllipse(-8, -8, 16, 16);
    painter->setPen(Qt::black);
    switch (m_type) {
    case StartNode:
        painter->drawText(-15, -20, 30, 14, Qt::AlignBottom | Qt::AlignHCenter, "Start");
        break;
    case EndNode:
        painter->drawText(-15, -20, 30, 14, Qt::AlignBottom | Qt::AlignHCenter, "End");
        break;
    default:
        break;
    }
}

QRectF GraphicsNodeItem::boundingRect() const
{
    return QRectF(-15, -25, 30, 35);
}

QPainterPath GraphicsNodeItem::shape() const
{
    QPainterPath path;
    path.addEllipse(-8, -8, 16, 16);
    return path;
}

void GraphicsNodeItem::setType(TypeNode type)
{
    m_type = type;
}

int GraphicsNodeItem::getType() const
{
    return m_type;
}

QVariant GraphicsNodeItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (change) {
    case ItemPositionHasChanged:
//        foreach (Edge *edge, edgeList)
//            edge->adjust();
//        graph->itemMoved();
        break;
    default:
        break;
    };

    return QGraphicsItem::itemChange(change, value);
}
