#ifndef ANTALGORITHM_H
#define ANTALGORITHM_H

#include <QObject>
#include <QVector>

class AntAlgorithm : public QObject
{
    Q_OBJECT

public:
    explicit AntAlgorithm(QObject *parent = 0);

    void run(int init, int finit);
    QVector<float> calculateProbability(QList<int> path, int node);
    void markPath(QList<int> path);
    QList<int> getOptimalPath(int init, int finit);

public slots:
    void setWeightM(QList< QVector<float> > weights);

signals:
    void strToLog(QString str);
    void optimalPathFound(QList<int> optimalPath);
    void showError(QString str);

private:
    void showM(QList<QVector<float> > m);

    float alpha;             // pheromon influence to choice
    float beta;              // distance influence to choice
    float vaporizationSpeed; // percent of feromon vaporization per step
    float mark;

    QList< QVector<float> > weightM;
    QList< QVector<float> > attractivenessM;
};

#endif // ANTALGORITHM_H
