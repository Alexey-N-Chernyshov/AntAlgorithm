#include <QVector>
#include <math.h>
#include "antalgorithm.h"
#include "ant.h"

AntAlgorithm::AntAlgorithm(QObject *parent) :
    QObject(parent),
    alpha(1.3),
    beta(1.1),
    vaporizationSpeed(0.05),
    mark(2.0)
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
}

void AntAlgorithm::run(int init, int finit)
{
    if (init < 0)
    {
        emit showError(tr("Начальная вершина не задана."));
        return;
    }
    if (finit < 0)
    {
        emit showError(tr("Конечная вершина не задана."));
        return;
    }

    emit strToLog(tr("Начало алгоритма.\n"));
    emit strToLog(tr("Матрица расстояний:"));
    showM(weightM);

    for (int i = 0; i < 10; ++i)
    {
        emit strToLog(tr("\nАгент №%1").arg(i).append(tr(" начал проход.")));
        Ant *ant = new Ant(this);
        ant->run(init, finit);
        delete ant;
        emit strToLog(tr("Агент №%1").arg(i).append(tr(" закончил проход.")));
    }

    QList<int> optPath = getOptimalPath(init, finit);
    emit strToLog(tr("Алгоритм закончен. Оптимальный путь:"));
    QString str;
    foreach (int i, optPath)
        str.append(QString("%1").arg(i).append(" "));
    emit strToLog(str);
    emit optimalPathFound(optPath);
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

    emit strToLog(tr("Агент в узле %1").arg(node).append(tr(". Вероятности перехода:")));
    QList< QVector<float> > list;
    list.append(probability);
    showM(list);
    return probability;
}

void AntAlgorithm::markPath(QList<int> path)
{
    //vaporize
    for (QList< QVector<float> >::iterator i = attractivenessM.begin(); i!= attractivenessM.end(); ++i)
        for (QVector<float>::iterator j = (*i).begin(); j != (*i).end(); ++j)
            (*j) *= (1 - vaporizationSpeed);

    //and mark
    int line = path.first();
    float pathLength = 0.;
    for (QList<int>::iterator i = (path.begin() + 1); i != path.end(); ++i)
    {
        pathLength += weightM.at(line).at(*i);
        line = (*i);
    }
    line = path.first();
    for (QList<int>::iterator i = (path.begin() + 1); i != path.end(); ++i)
    {
        attractivenessM[line][*i] += mark / pathLength;
        line = (*i);
    }
    emit strToLog(tr("Агент достиг конечной вершины, маркировка пути. Новая матрица маркировок:"));
    showM(attractivenessM);
}

QList<int> AntAlgorithm::getOptimalPath(int init, int finit)
{
    int cur = init;
    QList<int> res;
    for (int iter = 0; iter < attractivenessM.count(); ++iter)
    {
        res.append(cur);
        if (cur == finit)
            break;
        float max = attractivenessM.at(cur).first();
        int maxIndex = 0;
        for (int i = 1; i < attractivenessM.at(cur).count(); ++i)
            if (max < attractivenessM.at(cur).at(i))
            {
                max = attractivenessM.at(cur).at(i);
                maxIndex = i;
            }
        cur = maxIndex;
    }
    return res;
}

void AntAlgorithm::showM(QList<QVector<float> > m)
{
    QString str;
    for (QList<QVector<float> >::iterator i = m.begin(); i != m.end(); ++i)
    {
        for (QVector<float>::iterator j = (*i).begin(); j != (*i).end(); ++j)
            str.append(QString::number(*j)).append(" ");
        emit strToLog(str);
        str = "";
    }
}




