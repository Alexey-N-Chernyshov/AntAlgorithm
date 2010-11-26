#include <QGraphicsSceneMouseEvent>
#include <QVector>

#include "graphicsnodeitem.h"
#include "graphicsedgeitem.h"
#include "graphscene.h"

GraphScene::GraphScene(int w, int h, QObject *parent) :
        QGraphicsScene(parent),
        m_mode(AddPointMode),
        startLineNode(NULL),
        line(NULL),
        initialNode(NULL),
        finitNode(NULL)
{
    setSceneRect(0, 0, w, h);
}

void GraphScene::setContextMenuForPoint(QMenu *contextMenu)
{
    menu = contextMenu;
}

int GraphScene::getInit() const
{
    return listNodes.indexOf(initialNode);
}

int GraphScene::getFinit() const
{
    return listNodes.indexOf(finitNode);
}

QList< QVector<float> > GraphScene::getWeights()
{
    QList< QVector<float> > res;
    for (QList<GraphicsNodeItem *>::iterator i = listNodes.begin(); i != listNodes.end(); ++i)
    {
        QList< QPair<GraphicsNodeItem *, float> > connectedNodes = (*i)->getConnections();
        QVector<float> resWeights(listNodes.count(), 0.);
        for (QList< QPair<GraphicsNodeItem *, float> >::iterator j = connectedNodes.begin(); j != connectedNodes.end(); ++j)
            resWeights[listNodes.indexOf((*j).first)] = (*j).second;
        res.append(resWeights);
    }
    return res;
}

void GraphScene::setMode(Mode mode)
{
    m_mode = mode;
}

void GraphScene::setSelectMode()
{
    m_mode = SelectMode;
}

void GraphScene::setAddPoinrMode()
{
    m_mode = AddPointMode;
}

void GraphScene::setAddLineMode()
{
    m_mode = AddLineMode;
}

void GraphScene::setInitialPoint()
{
    if (!selectedItems().isEmpty())
        if (selectedItems().first()->type() == GraphicsNodeItem::Type)
        {
            if (initialNode)
                initialNode->setTypeNode(GraphicsNodeItem::IntermediateNode);
            initialNode = qgraphicsitem_cast<GraphicsNodeItem *>(selectedItems().first());
            initialNode->setTypeNode(GraphicsNodeItem::InitialNode);
        }
    update();
}

void GraphScene::setIntermediatePoint()
{
    if (!selectedItems().isEmpty())
        if (selectedItems().first()->type() == GraphicsNodeItem::Type)
            qgraphicsitem_cast<GraphicsNodeItem *>(selectedItems().first())->setTypeNode(GraphicsNodeItem::IntermediateNode);
    update();
}

void GraphScene::setFinitPoint()
{
    if (!selectedItems().isEmpty())
        if (selectedItems().first()->type() == GraphicsNodeItem::Type)
        {
            if (finitNode)
                finitNode->setTypeNode(GraphicsNodeItem::IntermediateNode);
            finitNode = qgraphicsitem_cast<GraphicsNodeItem *>(selectedItems().first());
            finitNode->setTypeNode(GraphicsNodeItem::FinitNode);
        }
    update();
}

void GraphScene::deleteSelectedItems()
{
    //firstly delete edges
    foreach (QGraphicsItem *item, selectedItems())
        if (item->type() == GraphicsEdgeItem::Type)
            delete item;

    //then delete nodes
    foreach (QGraphicsItem *item, selectedItems())
    {
        if (item == initialNode)
            initialNode = NULL;
        if (item == finitNode)
            finitNode = NULL;
        listNodes.removeAll(qgraphicsitem_cast<GraphicsNodeItem *>(item));
        delete item;
    }
    nodesChanged();
}

void GraphScene::nodesChanged()
{
    emit signalNodesChanged(getWeights());
}

void GraphScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() != Qt::LeftButton)
        return;

    switch (m_mode)
    {
        case AddPointMode:
        {
             GraphicsNodeItem *newNode = new GraphicsNodeItem(menu);
             //first node automatically set to initial
             if (items().isEmpty())
             {
                 newNode->setTypeNode(GraphicsNodeItem::InitialNode);
                 initialNode = newNode;
             }
             addItem(newNode);
             listNodes.append(newNode);
             newNode->setPos(event->scenePos());
             nodesChanged();
             break;
        }
        case AddLineMode:
        {
            QGraphicsItem *startItem = itemAt(event->scenePos());
            if ((startItem) && (startItem->type() == GraphicsNodeItem::Type))
            {
                startLineNode = qgraphicsitem_cast<GraphicsNodeItem *>(startItem);
                line = new QGraphicsLineItem(QLineF(startLineNode->pos(), event->scenePos()), 0, this);
                line->setPen(QPen(QColor(Qt::darkGray).lighter(150), 3));
                line->setZValue(-4);
            }
            break;
        }
        case SelectMode:
            break;
        default:
            break;
    }
    QGraphicsScene::mousePressEvent(event);
}

void GraphScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if ((m_mode == AddLineMode) && (line))
    {
        clearSelection();
        startLineNode->setSelected(true);
        QGraphicsItem *hoveredItem = itemAt(event->scenePos());
        if (hoveredItem && (hoveredItem->type() == GraphicsNodeItem::Type))
            hoveredItem->setSelected(true);
        line->setLine(QLineF(line->line().p1(), event->scenePos()));
    }
    else
        QGraphicsScene::mouseMoveEvent(event);
}

void GraphScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_mode == AddLineMode)
    {
        QGraphicsItem *destItem = itemAt(event->scenePos());
        if ((line) && (destItem) && (destItem->type() == GraphicsNodeItem::Type))
        {
            GraphicsNodeItem *destNode = qgraphicsitem_cast<GraphicsNodeItem *>(destItem);
            if (!destNode->isConnected(startLineNode))
            {
                GraphicsEdgeItem *newEdge = new GraphicsEdgeItem(startLineNode, destNode);
                addItem(newEdge);
                nodesChanged();
            }
        }

        startLineNode = NULL;
        if (line)
        {
            removeItem(line);
            delete line;
        }
        line = NULL;

        clearSelection();
        QGraphicsScene::mouseReleaseEvent(event);
    }
    else
        QGraphicsScene::mouseReleaseEvent(event);
}
