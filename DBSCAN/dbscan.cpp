#include "dbscan.h"

QVector<int> DBSCAN::start(QVector<double> col1, QVector<double> col2, int minPoints, double eps, int nlinhas)
{
    this->minPoints = minPoints;
    this->nLinhas   = nlinhas;
    this->col1 = col1;
    this->col2 = col2;
    this->eps  = eps;
    grupoQueoDadoPertence.clear();
    visitado.clear();
    id_grupo = 1; // C = 0

    // Nenhum dado foi visitado ainda
    // Nenhum grupo criado
    for (int var = 0; var < nLinhas; ++var)
    {
        visitado.append( false );
        grupoQueoDadoPertence.append( -1 );
    }

    // ############################# - Calula a distancia - ####################################
    QVector<double> distancia[nLinhas];
    for (int l = 0; l < nLinhas; ++l)
        for (int c = 0; c < nLinhas; ++c)
            distancia[l].append( sqrt( pow((col1.at(c)-col1.at(l)), 2) + pow((col2.at(c)-col2.at(l)), 2) ) ); // raiz quadrada( (Xb-Xa)^2 + (Yb-Ya)^2 )
    // #####################################################################################################

    // for each point P in dataset D {
    for (int p = 0; p < nLinhas; ++p) // Percorre todos os pontos
    {
        // if P is not visited
        if( visitado.at(p) == false ) // Se ainda não foi visitado
        {
            // mark P as visited
            visitado[p] = true; // Marca o dado como visitado
            // NeighborPts = regionQuery(P, eps)
            QVector<int> neighborPts = regionQuery(p, distancia); // Pega todos os vizinhos de P

            // if sizeof(NeighborPts) < MinPts
            if( neighborPts.length() < minPoints )
                // mark P as NOISE
                grupoQueoDadoPertence[p] = 1; // Pertence ao grupo 0 pq é ruído
            else
            {
                // C = next cluster
                id_grupo++;
                expandCluster(p, neighborPts, distancia);
            }
        }
    }

    // Agrupa em um novo vetor os grupos formados anteriormente
    QVector<int> grupos;
    for(int var = 1; var <= id_grupo; ++var)
    {
        grupos.append(0);
        for (int temp = 0; temp < grupoQueoDadoPertence.length(); ++temp)
            if( grupoQueoDadoPertence.at(temp) == var )
                grupos[var-1] += 1;
    }

    return grupos;
}

QVector<int> DBSCAN::regionQuery(int p, QVector<double> *distancia)
{
    QVector<int> neighbors;
    for (int var = 0; var < nLinhas; ++var)
        if( distancia[p].at(var) <= eps )
            neighbors.append( var );

    return neighbors;
}

void DBSCAN::expandCluster(int p, QVector<int> neighborPts, QVector<double> *distancia)
{
    // add P to cluster C
    grupoQueoDadoPertence[p] = id_grupo;

    // for each point P' in NeighborPts {
    for (int pLinha = 0; pLinha < neighborPts.length(); ++pLinha)
    {
        int aux = neighborPts[pLinha];
        // if P' is not visited {
        if( visitado[aux] == false )
        {
            // mark P' as visited
            visitado[aux] = true;
            // NeighborPts' = regionQuery(P', eps)
            QVector<int> neighborPtsLinha = regionQuery(aux, distancia);
            // if sizeof(NeighborPts') >= MinPts
            if( neighborPtsLinha.length() >= minPoints )
                // NeighborPts = NeighborPts joined with NeighborPts'
                neighborPts += neighborPtsLinha; // ACHO QUE ESTA AQUI O PROBLEMA
        }
        // if P' is not yet member of any cluster
        if( grupoQueoDadoPertence[aux] == -1 )
            // add P' to cluster C
            grupoQueoDadoPertence[aux] = id_grupo;
    }
}
