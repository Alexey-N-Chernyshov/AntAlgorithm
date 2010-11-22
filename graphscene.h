#ifndef GRAPHSCENE_H
#define GRAPHSCENE_H

#include <QGraphicsScene>

class GraphScene : public QGraphicsScene
{
    Q_OBJECT

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

public:
    explicit GraphScene(QObject *parent = 0);

signals:

public slots:

};

#endif // GRAPHSCENE_H
