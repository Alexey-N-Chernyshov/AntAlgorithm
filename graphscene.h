#ifndef GRAPHSCENE_H
#define GRAPHSCENE_H

#include <QGraphicsScene>

class QMenu;
class GraphicsNodeItem;

class GraphScene : public QGraphicsScene
{
    Q_OBJECT

public:
    enum Mode { AddPointMode, AddLineMode, SelectMode };

    explicit GraphScene(int w, int h, QObject *parent = 0);

    void setContextMenuForPoint(QMenu *contextMenu);

public slots:
    void setMode(Mode mode);
    void setSelectMode();
    void setAddPoinrMode();
    void setAddLineMode();

    void setInitialPoint();
    void setIntermediatePoint();
    void setFinitPoint();
    void deleteSelectedItems();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    QMenu *menu;
    Mode m_mode;
    QGraphicsLineItem *line;
    GraphicsNodeItem *initialNode;
    GraphicsNodeItem *finitNode;
};

#endif // GRAPHSCENE_H
