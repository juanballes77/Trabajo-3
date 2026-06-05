#include "meta.h"
#include <QBrush>
#include <QPen>

Meta::Meta(float x, float y, float ancho, float alto, QObject *parent)
    : QObject(parent),
    QGraphicsRectItem(x, y, ancho, alto)
{
    // Rectángulo dorado como meta temporal
    setBrush(QBrush(QColor(255, 215, 0)));       // Dorado
    setPen(QPen(QColor(255, 255, 255), 3));       // Borde blanco
    setZValue(0);
}
