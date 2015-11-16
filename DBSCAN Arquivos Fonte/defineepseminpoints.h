#ifndef DEFINEEPSEMINPOINTS_H
#define DEFINEEPSEMINPOINTS_H

#include <QVector>
#include <math.h>
#include <QDebug>

class DefineEPSeMinPoints
{
public:
    void start(QVector<double> col1, QVector<double> col2);

    int getMinPoints() const;

    double getEps() const;

private:
    int minPoints;
    double eps;
};

#endif // DEFINEEPSEMINPOINTS_H
