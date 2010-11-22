#include <QGraphicsSceneMouseEvent>

#include "graphicsnodeitem.h"
#include "graphicsedgeitem.h"
#include "graphscene.h"

GraphScene::GraphScene(QObject *parent) :
    QGraphicsScene(parent)
{
    GraphicsNodeItem *newNode1 = new GraphicsNodeItem();
    GraphicsNodeItem *newNode2 = new GraphicsNodeItem();
    GraphicsEdgeItem *newEdge = new GraphicsEdgeItem(newNode1, newNode2);
    addItem(newNode1);
    addItem(newNode2);
    addItem(newEdge);
    newNode1->setPos(10, 10);
    newNode2->setPos(100, 10);
    newNode1->setTypeNode(GraphicsNodeItem::StartNode);
    newNode2->setTypeNode(GraphicsNodeItem::EndNode);
}

void GraphScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    GraphicsNodeItem *newNode = new GraphicsNodeItem();
    addItem(newNode);
    newNode->setPos(event->pos());
    newNode->setTypeNode(GraphicsNodeItem::StartNode);
    QGraphicsScene::mousePressEvent(event);
}
