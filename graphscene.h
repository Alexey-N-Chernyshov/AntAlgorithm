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
    int getInit() const;
    int getFinit() const;

public slots:
    void setMode(Mode mode);
    void setSelectMode();
    void setAddPoinrMode();
    void setAddLineMode();

    void setInitialPoint();
    void setIntermediatePoint();
    void setFinitPoint();

    void deleteSelectedItems();
    void nodesChanged();
    void drawEdgesGray();
    void drawOptimalPath(QList<int> optimalPath);

signals:
    void signalNodesChanged(QList< QVector<float> > weights);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    QList< QVector<float> > getWeights();

    QMenu *menu;
    Mode m_mode;
    GraphicsNodeItem *startLineNode;
    QGraphicsLineItem *line;
    GraphicsNodeItem *initialNode;
    GraphicsNodeItem *finitNode;
    QList<GraphicsNodeItem *> listNodes;
};

#endif // GRAPHSCENE_H
