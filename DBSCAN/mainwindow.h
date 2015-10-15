#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QVector>
#include <QDebug>

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

private slots:
    void start();

    void mostraGrupos(QVector<int> grupos);
    void plot();

    void on_abreArquivo_clicked();

    void on_startButton_clicked();

private:
    DBSCAN dbscan;
    Ui::MainWindow *ui;
    QString filePath;
    int n_linhas;
    double eps;
    int minPoints;
    QVector<double> col1;
    QVector<double> col2;
};

#endif // MAINWINDOW_H
