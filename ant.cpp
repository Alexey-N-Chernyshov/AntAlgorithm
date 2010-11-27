#include <QVector>
#include "antalgorithm.h"
#include "ant.h"


Ant::Ant(AntAlgorithm *parent) :
    QObject(parent),
    antAlgorithm(parent)
{
}

void Ant::run(int init, int finit)
{
    int currentNode = init;
    path.append(init);
    while (currentNode != -1)
    {
        currentNode = step(antAlgorithm->calculateProbability(path, currentNode));
        if (currentNode == finit)
        {
            antAlgorithm->markPath(path);
            break;
        }
    }
}

int Ant::step(QVector<float> a)
{
    int nextNode = -1;
    float p = static_cast<float>(qrand()) / RAND_MAX;
    float s = 0.;
    for (int i = 0; i < a.count(); ++i)
    {
        s += a.at(i);
        if (p < s)
        {
            nextNode = i;
            path.append(i);
            break;
        }
    }
    return nextNode;
}
