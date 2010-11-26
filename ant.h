#ifndef ANT_H
#define ANT_H

#include <QObject>

class AntAlgorithm;

class Ant : public QObject
{
    Q_OBJECT

public:
    explicit Ant(AntAlgorithm *parent);

    void run(int init, int finit);

private:
    int step(QVector<float> a);

    AntAlgorithm *antAlgorithm;
    QList<int> path;
};

#endif // ANT_H
