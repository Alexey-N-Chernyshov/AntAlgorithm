#include <QGraphicsSceneMouseEvent>

#include "graphicsnodeitem.h"
#include "graphicsedgeitem.h"
#include "graphscene.h"

GraphScene::GraphScene(int w, int h, QObject *parent) :
    QGraphicsScene(parent)
{
    m_mode = AddPointMode;
    line = 0;
    setSceneRect(0, 0, w, h);

//    GraphicsNodeItem *newNode1 = new GraphicsNodeItem();
//    GraphicsNodeItem *newNode2 = new GraphicsNodeItem();
//    GraphicsEdgeItem *newEdge = new GraphicsEdgeItem(newNode1, newNode2);
//    addItem(newNode1);
//    addItem(newNode2);
//    addItem(newEdge);
//    newNode1->setPos(10, 10);
//    newNode2->setPos(100, 10);
//    newNode1->setTypeNode(GraphicsNodeItem::StartNode);
//    newNode2->setTypeNode(GraphicsNodeItem::EndNode);
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

void GraphScene::deleteSelectedItems()
{
    ;
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
        GraphicsNodeItem *newNode = new GraphicsNodeItem();
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
