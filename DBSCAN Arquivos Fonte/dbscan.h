#ifndef DBSCAN_H
#define DBSCAN_H

#include <QDebug>
#include <QVector>
#include <math.h>

class DBSCAN
{
public:
    QVector<int> start(QVector<double> col1, QVector<double> col2, int minPoints, double eps, int nlinhas);

private:
    QVector<int> regionQuery(int p, QVector<double> *distancia);
    void expandCluster(int p, QVector<int> neighborPts, QVector<double> *distancia);

private:
    int nLinhas;
    int minPoints;
    double eps;
    QVector<double> col1;
    QVector<double> col2;

    QVector<int> grupoQueoDadoPertence;
    int id_grupo;
    QVector<bool> visitado;
};

#endif // DBSCAN_H
