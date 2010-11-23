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

    switch (m_mode) {
    case SelectMode:
        QGraphicsScene::mousePressEvent(event);
        break;
    case AddPointMode:
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
    //QGraphicsScene::mousePressEvent(event);

//    GraphicsNodeItem *newNode = new GraphicsNodeItem();
//    addItem(newNode);
//    newNode->setPos(event->pos());
//    newNode->setTypeNode(GraphicsNodeItem::StartNode);
//    QGraphicsScene::mousePressEvent(event);
}

void GraphScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseMoveEvent(event);
}

void GraphScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseReleaseEvent(event);
}
