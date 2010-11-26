#include <QGraphicsScene>
#include <QPainter>
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>

#include "graphicsnodeitem.h"
#include "graphicsedgeitem.h"

GraphicsNodeItem::GraphicsNodeItem(QMenu *contextMenu, QGraphicsItem *parent) :
        QGraphicsItem(parent),
        m_type(IntermediateNode),
        menu(contextMenu)
{
    setFlags(ItemIsSelectable | ItemIsMovable | ItemSendsGeometryChanges | ItemIsFocusable);
    setZValue(-1);
}

GraphicsNodeItem::~GraphicsNodeItem()
{
    foreach (GraphicsEdgeItem *edge, edges)
        delete edge;
    scene()->removeItem(this);
}

void GraphicsNodeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setPen(Qt::NoPen);

    QRadialGradient gradient(-3, -3, 7);
    if (isSelected()) {
        gradient.setColorAt(0, QColor(Qt::white));
        gradient.setColorAt(1, QColor(Qt::darkGray));
    } else {
        gradient.setColorAt(0, Qt::white);
        gradient.setColorAt(1, Qt::black);
    }
    painter->setBrush(gradient);
    painter->drawEllipse(-8, -8, 16, 16);
    painter->setPen(Qt::black);
    switch (m_type)
    {
        case InitialNode:
            painter->drawText(-15, -20, 30, 14, Qt::AlignBottom | Qt::AlignHCenter, "Start");
            break;
        case FinitNode:
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

int GraphicsNodeItem::type() const
{
    return Type;
}

void GraphicsNodeItem::setTypeNode(TypeNode typeNode)
{
    m_type = typeNode;
}

int GraphicsNodeItem::typeNode() const
{
    return m_type;
}

void GraphicsNodeItem::addEdge(GraphicsEdgeItem *edge)
{
    edges.append(edge);
}

void GraphicsNodeItem::removeEdge(GraphicsEdgeItem *edge)
{
    edges.removeAll(edge);
}

bool GraphicsNodeItem::isConnected(GraphicsNodeItem *otherNode)
{
    foreach (GraphicsEdgeItem *edge, edges)
        if ((edge->getSourceNode() == otherNode) || (edge->getDestinationNode() == otherNode))
            return true;
    return false;
}

QVariant GraphicsNodeItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (change)
    {
        case ItemPositionHasChanged:
            foreach (GraphicsEdgeItem *edge, edges)
                edge->update();
            break;
        default:
            break;
    };

    return QGraphicsItem::itemChange(change, value);
}

void GraphicsNodeItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    scene()->clearSelection();
    setSelected(true);
    menu->exec(event->screenPos());
}

