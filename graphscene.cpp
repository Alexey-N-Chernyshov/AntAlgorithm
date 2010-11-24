#include <QGraphicsSceneMouseEvent>

#include "graphicsnodeitem.h"
#include "graphicsedgeitem.h"
#include "graphscene.h"

GraphScene::GraphScene(int w, int h, QObject *parent) :
        QGraphicsScene(parent),
        m_mode(AddPointMode),
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
            initialNode = qgraphicsitem_cast<GraphicsNodeItem *>(selectedItems()[0]);
            initialNode->setTypeNode(GraphicsNodeItem::InitialNode);
        }

    update();
}

void GraphScene::setIntermediatePoint()
{
    if (!selectedItems().isEmpty())
        if (selectedItems().first()->type() == GraphicsNodeItem::Type)
            qgraphicsitem_cast<GraphicsNodeItem *>(selectedItems()[0])->setTypeNode(GraphicsNodeItem::IntermediateNode);
    update();
}

void GraphScene::setFinitPoint()
{
    if (!selectedItems().isEmpty())
        if (selectedItems().first()->type() == GraphicsNodeItem::Type)
        {
            if (finitNode)
                finitNode->setTypeNode(GraphicsNodeItem::IntermediateNode);
            finitNode = qgraphicsitem_cast<GraphicsNodeItem *>(selectedItems()[0]);
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
        delete item;
    }
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
             if (items().isEmpty())
             {
                 newNode->setTypeNode(GraphicsNodeItem::InitialNode);
                 initialNode = newNode;
             }
             addItem(newNode);
             newNode->setPos(event->scenePos());
             break;
        }
        case AddLineMode:
        {
            QGraphicsItem *startItem = itemAt(event->scenePos());
            if ((startItem) && (startItem->type() == GraphicsNodeItem::Type))
            {
                line = new QGraphicsLineItem(QLineF(startItem->pos(), startItem->pos()), 0, this);
                line->setPen(QPen(QColor(Qt::darkGray).lighter(150), 3));
                line->setZValue(-3);
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
        itemAt(line->line().p1())->setSelected(true);
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
        if (line)
        {
            QGraphicsItem *destItem = itemAt(event->scenePos());
            if (destItem && (destItem->type() == GraphicsNodeItem::Type))
            {
                GraphicsEdgeItem *newEdge = new GraphicsEdgeItem(qgraphicsitem_cast<GraphicsNodeItem *>(itemAt(line->line().p1())),
                                                                 qgraphicsitem_cast<GraphicsNodeItem *>(destItem));
                addItem(newEdge);
            }
            removeItem(line);
            if (line)
                delete line;
            line = NULL;
        }
        clearSelection();
        QGraphicsScene::mouseReleaseEvent(event);
    }
    else
        QGraphicsScene::mouseReleaseEvent(event);
}
