#ifndef GRAPHICSTEXTITEM_H
#define GRAPHICSTEXTITEM_H

#include <QGraphicsTextItem>

class GraphicsTextItem : public QGraphicsTextItem
{
    Q_OBJECT

public:
    explicit GraphicsTextItem(QString str, QGraphicsItem *parent = 0);

protected:
    void keyPressEvent(QKeyEvent *event);

};

#endif // GRAPHICSTEXTITEM_H
