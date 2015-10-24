#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    sceneW = 650;
    sceneH = 590;

    scene = new QGraphicsScene(0, 0, sceneW, sceneH);
    ui->graphicsView->setScene(scene);

    QMatrix m;
    m.translate(0, sceneH);
    m.scale(1, -1); // Inverte o eixo da scene

    ui->graphicsView->setMatrix(m);

    ui->graphicsView->installEventFilter(this);

    pontos = 0;

    //scene->mousePressEvent(QGraphicsSceneMouseEvent *event);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);

        xValues.append( mouseEvent->pos().x() );
        yValues.append( sceneH-mouseEvent->pos().y() );
        pontos++;
        ui->labelPontos->setText("Pontos: " + QString::number(pontos) );

        ui->labelX->setText("X: " + QString::number( mouseEvent->pos().x() ) );
        ui->labelY->setText("Y: " + QString::number( sceneH-mouseEvent->pos().y() ) );

        QBrush blueBrush(Qt::blue);
        QPen blackPen(Qt::black);
        blackPen.setWidth(2);
        scene->addEllipse(mouseEvent->pos().x()-2, sceneH-mouseEvent->pos().y()-2, 5, 5, blackPen, blueBrush);

        ui->salvarPushButton->setEnabled(true);
        ui->start2PushButton->setEnabled(true);

        return true;
    } else {
        // standard event processing
        return QObject::eventFilter(obj, event);
    }
}

void MainWindow::start()
{
    // Lê os valores dos campos
    int coluna1 = ui->col1SpinBox->value();
    int coluna2 = ui->col2SpinBox->value();
    minPoints   = ui->minPointsSpinBox->value();
    eps         = ui->epsSpinBox->value();

    // Limpa os vetores
    col1.clear();
    col2.clear();

    if( filePath.isEmpty() )
        return;

    // Testa abrir o arquivo para leitura
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, tr("Erro"), tr("Não foi possível abrir o arquivo"));
        return;
    }

    // Checa se o arquivo tem cabeçalho, se sim, descarta ele
    if( ui->cabecalhoCheckBox->isChecked() )
        file.readLine();

    n_linhas = 0; // Zera o número de linhas, para começar a contar

    while(!file.atEnd())
    {
        QString line = file.readLine(); // Lê uma linha no arquivo
        col1.append( line.split(",").at(coluna1-1).toDouble() ); // Lê a coluna 1
        col2.append( line.split(",").at(coluna2-1).toDouble() ); // Lê a coluna 2
        n_linhas++; // Conta o número de linhas
    }

    file.close(); // Fecha o arquivo

    // Chama o DBSCAN e aguarda o resultado, que será um vetor com a quantidade de dados por grupo
    QVector<int> grupos = dbscan.start(col1, col2, minPoints, eps, n_linhas);

    // Chama a função que mostra os dados na tela
    mostraGrupos(grupos);

    // Chama a função que plota os dados na tela
    plot();
}

void MainWindow::mostraGrupos(QVector<int> grupos)
{
    // Limpa o campo e coloca os pontos, eps e minpoiints
    ui->saidaPlainTextEdit->clear();
    ui->saidaPlainTextEdit->appendPlainText( "Pontos : "      + QString::number(n_linhas) +
                                             ", eps : "       + QString::number(eps) +
                                             ", MinPoints : " + QString::number(minPoints) + "\n" );

    QString conteudo;
    for (int var = 0; var < grupos.length(); var++)
        conteudo += "Grupo " + QString::number(var) + " : " + QString::number( grupos.at(var) ) + "  |  ";

    ui->saidaPlainTextEdit->appendPlainText( conteudo );

}

void MainWindow::plot()
{
    // Add o gráfico, seta os dados das colunas x e y, seta o label, o estilo e a interação
    ui->plot->addGraph();
    ui->plot->graph(0)->setData(col1, col2);
    ui->plot->xAxis->setLabel("Coluna 1");
    ui->plot->yAxis->setLabel("Coluna 2");
    ui->plot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle));
    ui->plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    // Acha o minimo e o máximo de cada coluna para posicionar o gráfico de acordo com os dados
    double min = col1.at(0);
    double max = col1.at(0);
    for (int var = 0; var < col1.length(); ++var) {
        if( col1.at(var) < min )
            min = col1.at(var);
        if( col1.at(var) > max )
            max = col1.at(var);
    }
    ui->plot->xAxis->setRange(min, max);

    min = col2.at(0);
    max = col2.at(0);
    for (int var = 0; var < col2.length(); ++var) {
        if( col2.at(var) < min )
            min = col2.at(var);
        if( col2.at(var) > max )
            max = col2.at(var);
    }
    ui->plot->yAxis->setRange(min, max);

    ui->plot->replot();
}

void MainWindow::on_abreArquivo_clicked()
{
    // Pega o caminho do arquivo
    filePath = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("All Files ()"));
    ui->caminhoDoArquivoEdit->setText(filePath); // Mostra o caminho no edit
    ui->startButton->setEnabled(true); // Libera o botão
    ui->carregarPushButton->setEnabled(true);
}

void MainWindow::on_startButton_clicked()
{
    // Checa se o valor das colunas não são os mesmos e chama a função start
    if( ui->col1SpinBox->value() != ui->col2SpinBox->value() )
        start();
}

void MainWindow::on_pushButton_2_clicked()
{
    xValues.clear();
    yValues.clear();
    pontos = 0;
    ui->labelPontos->setText("Pontos: 0" );
    ui->labelX->setText("X: -");
    ui->labelY->setText("Y: -");
    scene->clear();
    ui->salvarPushButton->setEnabled(false);
    ui->start2PushButton->setEnabled(false);
}

void MainWindow::on_salvarPushButton_clicked()
{
    QString Filename = QFileDialog::getSaveFileName(this, "Save file", "filename.csv", "CSV files (.csv);;", 0, 0); // getting the filename (full path)

    QFile mFile(Filename);

    if(!mFile.open(QFile::WriteOnly | QFile::Text))
    {
        qDebug() << "Could not open file for writting";
        return;
    }

    QTextStream out(&mFile);

    out << "x,";
    out << "y" << "\n";

    for (int var = 0; var < xValues.length(); ++var)
    {
        out << QString::number( xValues.at(var) );
        out << ",";
        out << QString::number( yValues.at(var) );
        if( var != xValues.length()-1 )
            out << "\n";
    }

    QMessageBox::information(this, "Salvo", "Salvo com sucesso!");

    mFile.flush();
    mFile.close();
}

void MainWindow::on_start2PushButton_clicked()
{
    // START 2
    // CHAMAR DBSCAN DE OUTRA FORMA
    if( xValues.isEmpty() )
    {
        QMessageBox::information(this, "Informação", "Crie pontos antes de clicar no botão Start.");
        return;
    }

    minPoints   = ui->minPointsSpinBox->value();
    eps         = ui->epsSpinBox->value();
    n_linhas    = xValues.length();

    col1.clear();
    col2.clear();

    col1 = xValues;
    col2 = yValues;

    // Chama o DBSCAN e aguarda o resultado, que será um vetor com a quantidade de dados por grupo
    QVector<int> grupos = dbscan.start(col1, col2, minPoints, eps, n_linhas);

    // Chama a função que mostra os dados na tela
    mostraGrupos(grupos);

    // Chama a função que plota os dados na tela
    plot();
}

void MainWindow::on_carregarPushButton_clicked()
{
    // Carregar dados

    // Limpa os vetores
    col1.clear();
    col2.clear();

    int coluna1 = ui->col1SpinBox->value();
    int coluna2 = ui->col2SpinBox->value();

    if( filePath.isEmpty() )
        return;

    // Testa abrir o arquivo para leitura
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, tr("Erro"), tr("Não foi possível abrir o arquivo"));
        return;
    }

    // Checa se o arquivo tem cabeçalho, se sim, descarta ele
    if( ui->cabecalhoCheckBox->isChecked() )
        file.readLine();

    while(!file.atEnd())
    {
        QString line = file.readLine(); // Lê uma linha no arquivo
        col1.append( line.split(",").at(coluna1-1).toDouble() ); // Lê a coluna 1
        col2.append( line.split(",").at(coluna2-1).toDouble() ); // Lê a coluna 2
    }

    file.close(); // Fecha o arquivo

    xValues = col1;
    yValues = col2;

    pontos = xValues.length();
    ui->labelPontos->setText("Pontos: " + QString::number(pontos) );

    ui->start2PushButton->setEnabled(true);

    QBrush blueBrush(Qt::red);
    QPen blackPen(Qt::black);
    blackPen.setWidth(2);

    scene->clear();

    for (int var = 0; var < pontos; ++var)
        scene->addEllipse(xValues.at(var), yValues.at(var), 5, 5, blackPen, blueBrush);

}
