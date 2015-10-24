# DBSCAN C++

Implementação do algoritmo DBSCAN em C++ com interface gráfica.

## Descrição

O DBSCAN (Density-based spatial clustering of applications with noise) é um algoritmo de agrupamento de dados, baseado em densidade, proposto por Martin Ester, Hans-Peter Kriegel, Jorg Sander e Xu Xiaowei em 1996. Dado um conjunto de pontos em um espaço, o algoritmo agrupa os pontos que possuem vizinhos mais próximos, e categoriza aqueles dados/pontos que estão em regiões de baixa densidade (onde os vizinhos estão longes) como ruído. O DBSCAN é um algoritmo bem comum e bastante citado na literatura científica.

### Parâmetros

O DBSCAN requer dois parâmetros:

- eps: distância entre os pontos. Significa que se a distância entre um ponto e outro é menor ou igual ao valor de eps, então estes dois pontos são considerados vizinhos.

- minPoints: número mínimo de pontos necessários para formar uma região densa. Por exemplo, se o minPoints é igual a 5 então são necessários 5 pontos para formar um região densa.

## Screenshot

![alt text](https://github.com/kelvins/DBSCAN/blob/master/screenshot.png "Screenshot")

> Obs.: Esta aplicação foi desenvolvida como estudo e trabalho para a disciplina de Mineração de Dados, por este e outros motivos, não segui algumas boas práticas de documentação e desenvolvimento.

Em todo caso, qualquer dúvida ou sugestão entre em contato pelo e-mail: kelvinpfw@hotmail.com
