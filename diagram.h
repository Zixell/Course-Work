#ifndef DIAGRAM_H
#define DIAGRAM_H

#include <QWidget>
#include <QPainter>
#include <QPointF>
#include <QVector>
#include <QString>

class Diagram : public QWidget
{
    Q_OBJECT

public:
    explicit Diagram(QColor col, QWidget *parent = 0);

    void loadData(QVector<QPointF> data); // Загрузка списка точек в график
    void pair(Diagram *d);                // Связка двух графиков
    qreal minX, maxX, minY, maxY;

private:

    QVector<QPointF> dataset;

    void paintEvent(QPaintEvent*);
    QColor lineColor;
    Diagram *myPair;
signals:

public slots:
};

#endif // DIAGRAM_H
