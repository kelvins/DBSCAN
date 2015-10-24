#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QVector>
#include <QDebug>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

#include "dbscan.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    bool eventFilter(QObject *obj, QEvent *event);
private slots:
    void start();

    void mostraGrupos(QVector<int> grupos);
    void plot();

    void on_abreArquivo_clicked();

    void on_startButton_clicked();

    void on_pushButton_2_clicked();

    void on_salvarPushButton_clicked();

    void on_start2PushButton_clicked();

    void on_carregarPushButton_clicked();

private:
    DBSCAN dbscan;
    Ui::MainWindow *ui;
    QString filePath;
    int n_linhas;
    double eps;
    int minPoints;
    QVector<double> col1;
    QVector<double> col2;
    QGraphicsScene *scene;
    QVector<double> xValues; // Values of the QGraphicsView
    QVector<double> yValues;
    int pontos;
    int sceneW;
    int sceneH;
};

#endif // MAINWINDOW_H
