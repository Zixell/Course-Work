#include "diagram.h"

Diagram::Diagram(QColor col, QWidget *parent) : QWidget(parent)
{
    lineColor = col;
    QVector<QPointF> startData;
    startData.push_back(QPointF(0.0, 0.0));
    loadData(startData);
    myPair = 0;
}

void Diagram::loadData(QVector<QPointF> data)
{
    dataset = data;

    minX = dataset.at(0).x();
    maxX = dataset.at(0).x();
    minY = dataset.at(0).y();
    maxY = dataset.at(0).y();

    foreach (QPointF point, dataset) {
        if(point.x() < minX) minX = point.x();
        if(point.x() > maxX) maxX = point.x();
        if(point.y() < minY) minY = point.y();
        if(point.y() > maxY) maxY = point.y();
    }
    repaint();
}

void Diagram::pair(Diagram *d)
{
    myPair = d;
}

void Diagram::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setPen(QPen(lineColor, 2, Qt::SolidLine));

    if(myPair) {
        maxY = maxY > myPair->maxY ? maxY : myPair->maxY;
    }

    QPointF lastPoint;
    if((maxX - minX) == 0) {
        lastPoint.setX(0.0);
    } else {
        lastPoint.setX( (dataset.at(0).x() - minX) / (maxX - minX) );
    }

    if((maxY - minY) == 0) {
        lastPoint.setY(1);
    } else {
        lastPoint.setY( 1 - (dataset.at(0).y() - minY) / (maxY - minY) );
    }

    lastPoint.setX( lastPoint.x()*width() );
    lastPoint.setY( lastPoint.y()*height() );

    foreach (QPointF point, dataset) {
        QPointF currentPoint;
        if((maxX - minX) == 0) {
            currentPoint.setX(0.0);
        } else {
            currentPoint.setX( (point.x() - minX) / (maxX - minX) );
        }

        if((maxY - minY) == 0) {
            currentPoint.setY(1);
        } else {
            currentPoint.setY( 1 - (point.y() - minY) / (maxY - minY) );
        }
        currentPoint.setX( currentPoint.x()*width() );
        currentPoint.setY( currentPoint.y()*height() );


        painter.drawLine(lastPoint, currentPoint);
        lastPoint = currentPoint;
    }
    painter.setPen(QPen(Qt::black,1,Qt::SolidLine));
    painter.drawText(5, height()-5, QString::number(minX) + "; " + QString::number(minY));
    painter.drawText(5, 10, QString::number(maxY));
    painter.drawText(width() - 25, height()-5, QString::number(maxX));
    painter.drawRect(0, 0, width()-1, height()-1);
}
