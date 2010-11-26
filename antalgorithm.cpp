#include <QVector>
#include <math.h>
#include "antalgorithm.h"
#include "ant.h"

AntAlgorithm::AntAlgorithm(QObject *parent) :
    QObject(parent),
    alpha(1.),
    beta(1.)
{
}

void AntAlgorithm::setWeightM(QList<QVector<float> > weights)
{
    weightM = weights;

    for (int i = 0; i < attractivenessM.count(); ++i)
        attractivenessM[i].clear();
    attractivenessM.clear();

    int n = weightM.count();
    for (int i = 0; i < n; ++i)
        attractivenessM.append(QVector<float>(n, 0.));

    ///////////////
    showM(weightM);
    ///////////////
}

void AntAlgorithm::run(int init, int finit)
{
    Ant *ant = new Ant(this);
    ant->run(init, finit);
    delete ant;
}

QVector<float> AntAlgorithm::calculateProbability(QList<int> path, int node)
{
    QVector<float> probability(attractivenessM.count(), 0);
    float denominator = 0.;

    for (int j = 0; j < attractivenessM.count(); ++j)
        if ((weightM.at(node).at(j) != 0.) && (!path.contains(j)))
            denominator += pow(attractivenessM.at(node).at(j), alpha) + pow(1 / weightM.at(node).at(j), beta);
        for (int j = 0; j < attractivenessM.count(); ++j)
            if ((weightM.at(node).at(j) != 0) && (!path.contains(j)) && (denominator != 0))
                probability[j] = (pow(attractivenessM.at(node).at(j), alpha) +
                                  pow(1 / weightM.at(node).at(j), beta)) / denominator;
            else
                probability[j] = 0.;

    return probability;
}

void AntAlgorithm::markPath(QList<int> path)
{
//    for (QList<int>::iterator i = path.begin(); i != path.end(); ++i)
//        attractivenessM[*i] = attractivenessM[*i] * (1 - vaporizationSpeed) + 1 / weightM.at(i);
//    recalculateAttractiveness();
}

/////////////////////////////////////////////
/////////////////////////////////////////////
void AntAlgorithm::showM(QList<QVector<float> > m)
{
    QString str;
    for (QList<QVector<float> >::iterator i = m.begin(); i != m.end(); ++i)
    {
        for (QVector<float>::iterator j = (*i).begin(); j != (*i).end(); ++j)
            str.append(QString::number(*j)).append(" ");
        qDebug() << str;
        str = "";
    }
    qDebug() << "------------------------------------------------------";
}
/////////////////////////////////////////////




