#include "enemigociclista.h"
#include <QBrush>
#include <QPen>
#include <cstdlib>

EnemigoCiclista::EnemigoCiclista(float x, float y, float ancho, float alto, QObject *parent)
    : Enemigo(x, y, 0, 0, 0, parent),
    ancho(ancho),
    alto(alto),
    velocidadExtra(3.0f)
{
    velocidadLateral = ((std::rand() % 5) - 2) * 1.0f;

    // Rectángulo naranja temporal
    QPixmap temporal(ancho, alto);
    temporal.fill(QColor(255, 140, 0));
    setPixmap(temporal);

    setZValue(0);
    setPos(x, y);
}

void EnemigoCiclista::actualizar()
{
    // Sin uso directo, se usa la versión con parámetros
}

void EnemigoCiclista::actualizar(float velocidadScroll, float limiteIzq, float limiteDer)
{
    y += velocidadScroll + velocidadExtra;

    x += velocidadLateral;
    if (x <= limiteIzq || x + ancho >= limiteDer)
        velocidadLateral = -velocidadLateral;

    setPos(x, y);
}

void EnemigoCiclista::cargarFrame(int indice)
{
    Q_UNUSED(indice)
    // Sin animación por ahora, se implementará con sprite
}
