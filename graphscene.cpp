#include "graphscene.h"

GraphScene::GraphScene(QObject *parent) :
    QGraphicsScene(parent)
{
}

void GraphScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    GraphicsNodeItem *newNode = new GraphicsNodeItem();
    addItem(newNode);
    newNode->setPos(event->pos());
    newNode->setType(GraphicsNodeItem::StartNode);
    QGraphicsScene::mousePressEvent(event);
}
