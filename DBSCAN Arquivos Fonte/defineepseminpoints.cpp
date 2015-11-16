#include "defineepseminpoints.h"

void DefineEPSeMinPoints::start(QVector<double> col1, QVector<double> col2)
{
    this->minPoints = 0;
    this->eps = 0;

    int nLinhas = col1.length();

    // ############################# - Calula a distancia - ####################################
    QVector<double> distancia[nLinhas];
    for (int l = 0; l < nLinhas; ++l)
        for (int c = 0; c < nLinhas; ++c)
            distancia[l].append( sqrt( pow((col1.at(c)-col1.at(l)), 2) + pow((col2.at(c)-col2.at(l)), 2) ) ); // raiz quadrada( (Xb-Xa)^2 + (Yb-Ya)^2 )
    // #####################################################################################################


    // ########## - Define o EPS e MinPoints - ############
    QVector<double> epsValues;
    for (int l = 0; l < nLinhas; ++l)
    {
        epsValues.append(0);
        for (int c = 0; c < nLinhas; ++c)
        {
            epsValues[l] += distancia[l].at(c);
        }
        epsValues[l] = epsValues.at(l)/nLinhas;
    }

    for (int temp = 0; temp < epsValues.length(); ++temp)
    {
        eps += epsValues.at(temp);
    }

    this->minPoints = (1/epsValues.length()) * eps;
    this->eps = eps / epsValues.length();

    qDebug() << minPoints;
    qDebug() << eps;

}

int DefineEPSeMinPoints::getMinPoints() const
{
    return minPoints;
}

double DefineEPSeMinPoints::getEps() const
{
    return eps;
}
