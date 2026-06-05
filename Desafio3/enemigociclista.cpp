#include "enemigociclista.h"
#include <QBrush>
#include <QPen>
#include <cstdlib>

EnemigoCiclista::EnemigoCiclista(float x, float y, float ancho, float alto, QObject *parent)
    : QObject(parent),
    QGraphicsRectItem(x, y, ancho, alto),
    x(x),
    y(y),
    velocidadExtra(3.0f)
{
    // Velocidad lateral aleatoria entre -2 y 2
    velocidadLateral = ((std::rand() % 5) - 2) * 1.0f;

    // Rectángulo naranja
    setBrush(QBrush(QColor(255, 140, 0)));
    setPen(QPen(QColor(200, 100, 0), 2));
    setZValue(0);
    setPos(x, y);
}

void EnemigoCiclista::actualizar(float velocidadScroll, float limiteIzq, float limiteDer)
{
    // Bajar con el scroll más velocidad extra
    y += velocidadScroll + velocidadExtra;

    // Moverse lateralmente y rebotar en los límites
    x += velocidadLateral;
    if (x <= limiteIzq || x + rect().width() >= limiteDer)
        velocidadLateral = -velocidadLateral;

    setPos(x, y);
}

float EnemigoCiclista::obtenerX() const { return x; }
float EnemigoCiclista::obtenerY() const { return y; }
