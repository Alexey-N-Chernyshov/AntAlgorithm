#ifndef GRAPHSCENE_H
#define GRAPHSCENE_H

#include <QGraphicsScene>

class GraphScene : public QGraphicsScene
{
    Q_OBJECT

public:
    enum Mode { AddPointMode, AddLineMode, SelectMode };

    explicit GraphScene(int w, int h, QObject *parent = 0);

public slots:
    void setMode(Mode mode);
    void setSelectMode();
    void setAddPoinrMode();
    void setAddLineMode();
    void deleteSelectedItems();

signals:

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    Mode m_mode;
    QGraphicsLineItem *line;
};

#endif // GRAPHSCENE_H
