#ifndef GRAPHICSNODEITEM_H
#define GRAPHICSNODEITEM_H

#include <QGraphicsItem>

class GraphicsEdgeItem;
class QMenu;

class GraphicsNodeItem : public QGraphicsItem
{
public:
    enum { Type = UserType + 11 };
    enum TypeNode { InitialNode, IntermediateNode, FinitNode };

    GraphicsNodeItem(QMenu *contextMenu, QGraphicsItem *parent = 0);
    ~GraphicsNodeItem();

    int type() const;
    void setTypeNode(TypeNode typeNode);
    int typeNode() const;
    void addEdge(GraphicsEdgeItem *edge);
    void removeEdge(GraphicsEdgeItem *edge);
    bool isConnected(GraphicsNodeItem *otherNode);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    QRectF boundingRect() const;
    QPainterPath shape() const;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

private:
    TypeNode m_type;
    QList<GraphicsEdgeItem *> edges;
    QMenu *menu;
};

#endif // GRAPHICSNODEITEM_H
