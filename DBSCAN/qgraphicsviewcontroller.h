#ifndef QGRAPHICSVIEWCONTROLLER_H
#define QGRAPHICSVIEWCONTROLLER_H


class QGraphicsViewController : public QGraphicsView
{
public:
    QGraphicsViewController();
    /*void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);*/
    void mousePressEvent(QMouseEvent *event);
    /*void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);*/

signals:

public slots:
};

#endif // QGRAPHICSVIEWCONTROLLER_H
