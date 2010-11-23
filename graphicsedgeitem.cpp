#include <QGraphicsScene>
#include <QPainter>

#include "graphicsedgeitem.h"
#include "graphicsnodeitem.h"
#include "graphicstextitem.h"

GraphicsEdgeItem::GraphicsEdgeItem(GraphicsNodeItem *sourceNode, GraphicsNodeItem *destNode, QGraphicsItem *parent) :
    QGraphicsItem(parent),
    lowerValue(0.),
    showLowerValue(false)
{
    source = sourceNode;
    sourceNode->addEdge(this);
    dest = destNode;
    destNode->addEdge(this);
    setFlags(ItemIsSelectable | ItemSendsGeometryChanges | ItemIsFocusable);
    setZValue(-2);
    line = new QGraphicsLineItem(this);
    upperTextItem = new GraphicsTextItem("1", this);
}

GraphicsEdgeItem::~GraphicsEdgeItem()
{
    source->removeEdge(this);
    dest->removeEdge(this);
    scene()->removeItem(this);

    delete line;
    delete upperTextItem;
}

int GraphicsEdgeItem::type() const
{
    return Type;
}

void GraphicsEdgeItem::setLowerValue(double val)
{
    lowerValue = val;
}

void GraphicsEdgeItem::setShowLowerValue(bool val)
{
    showLowerValue = val;
}


QRectF GraphicsEdgeItem::boundingRect() const
{
    return QRectF(qMin(source->pos().x(), dest->pos().x()) - 25, qMin(source->pos().y(), dest->pos().y()) - 25,
                  qAbs(source->pos().x() - dest->pos().x()) + 50, qAbs(source->pos().y() - dest->pos().y()) + 50);
}

QPainterPath GraphicsEdgeItem::shape() const
{
    return line->shape();
}

void GraphicsEdgeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    if (!source || !dest)
        return;

    QColor colorLine = Qt::darkGray;
    if (isSelected())
        colorLine = colorLine.lighter(150);

    line->setPen(QPen(colorLine, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    line->setLine(QLineF(source->pos(), dest->pos()));

    upperTextItem->setPos((source->pos().x() + dest->pos().x()) / 2 - 20,
                          (source->pos().y() + dest->pos().y()) / 2 - 22);
    if (showLowerValue)
        painter->drawText((source->pos().x() + dest->pos().x()) / 2 - 20,
                          (source->pos().y() + dest->pos().y()) / 2 + 3,
                          40, 14, Qt::AlignTop | Qt::AlignHCenter, QString::number(lowerValue));
}
