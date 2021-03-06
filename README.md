# DBSCAN C++

Implementação do algoritmo de agrupamento DBSCAN em C++ com interface gráfica.

## Descrição

O DBSCAN (Density-based spatial clustering of applications with noise) é um algoritmo de agrupamento de dados, baseado em densidade, proposto por Martin Ester, Hans-Peter Kriegel, Jorg Sander e Xu Xiaowei em 1996. Dado um conjunto de pontos em um espaço, o algoritmo agrupa os pontos que possuem vizinhos mais próximos, e categoriza aqueles dados/pontos que estão em regiões de baixa densidade (onde os vizinhos estão longes) como ruído. O DBSCAN é um algoritmo bem comum e bastante citado na literatura científica.

### Parâmetros

O DBSCAN requer dois parâmetros:

- eps: distância entre os pontos. Significa que se a distância entre um ponto e outro é menor ou igual ao valor de eps, então estes dois pontos são considerados vizinhos.

- minPoints: número mínimo de pontos necessários para formar uma região densa. Por exemplo, se o minPoints é igual a 5 então são necessários 5 pontos para formar um região densa.

## Instruções

- Botão Arquivo: é possível selecionar e carregar um arquivo no formato CSV.
- Campos Coluna 1 e Coluna 2: são utilizados para selecionar as colunas desejadas do arquivo carregado.
- Possui Cabeçalho: este campo deve ser selecionado se o arquivo possui cabeçalho, pois ele é utilizado para ignorar ou não a primeira linha do arquivo CSV.
- MinPoints: número mínimo de pontos para formar uma região densa. Um dos parâmetros do DBSCAN.
- eps: distância máxima entre os pontos para serem considerados vizinhos. Outro parâmetro do DBSCAN.
- Botão START esquerdo (grupo de configurações): utilizado para rodar o DBSCAN nos dados carregados (arquivo CSV) e configurados.
- Campo de Saída: mostra as informações utilizadas no DBSCAN e a quantidade de grupos com seus respectivos pontos.
- Gráfico: apenas plota os dados para facilitar a visualização.
- Janela vazia do lado direito: clicando nela é possível criar pontos para testar o DBSCAN, e também é possível salvar estes pontos em um arquivo CSV posteriormente. É basicamente uma área de criação/edição de pontos/dados que pode ser utilizada principalmente para fins de teste e/ou didáticos.
- Botão Carregar Dados: carrega os dados do arquivo CSV (carregado nas configurações) para a área de edição.
- Botão Salvar: permite salvar os dados criados/editados em um arquivo .CSV.
- Botão Limpar: limpa a área de criação/edição.
- Botão Start direito (grupo de  opções): chama o DBSCAN passando os dados que estão na área de criação/edição.
- Botão Salvar o Gráfico como Imagem: permite salvar o gráfico como uma imagem.
- Botão Salvar Resultado em CSV: permite salvar o resultado do DBScan em CSV, sendo que cada linha irá apresentar o grupo referente ao ponto em que ele pertence.


## Screenshot 1

![alt text](https://github.com/kelvins/DBSCAN/blob/master/screenshot1.png "Screenshot")

## Screenshot 2

![alt text](https://github.com/kelvins/DBSCAN/blob/master/screenshot2.png "Screenshot")

## Screenshot 3

![alt text](https://github.com/kelvins/DBSCAN/blob/master/screenshot3.png "Screenshot")

> Obs.: Esta aplicação foi desenvolvida como estudo e trabalho para a disciplina de Mineração de Dados e tem como objetivo ser utilizada para o desenvolvimento do trabalho e posteriormente para fins didáticos do algoritmo DBScan. O algoritmo implementado foi baseado no estudo do artigo original "A Density-Based Algorithm for Discovering Clusters in Large Spatial Databases with Noise" e no pseudocódigo apresentado no seguinte link: https://en.wikipedia.org/wiki/DBSCAN

Qualquer dúvida ou sugestão sobre a aplicação entre em contato pelo e-mail: kelvinpfw@hotmail.com
