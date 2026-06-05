#include "enemigociclista.h"
#include <cstdlib>

EnemigoCiclista::EnemigoCiclista(float x, float y, float ancho, float alto, QObject *parent)
    : Enemigo(x, y, 0, 0, 0, parent),
    ancho(ancho),
    alto(alto),
    contadorFrame(0),
    velocidadExtra(3.0f),
    frameAnimacion(0)
{
    velocidadLateral = ((std::rand() % 5) - 2) * 1.0f;

    // Cargar sprite del ciclista rival (rojo)
    hojaCiclista = QPixmap(":/ciclista.png");
    cargarFrameCiclista(0);

    setZValue(0);
    setPos(x, y);
}

void EnemigoCiclista::actualizar()
{
    // Sin uso directo
}

void EnemigoCiclista::actualizar(float velocidadScroll, float limiteIzq, float limiteDer)
{
    y += velocidadScroll + velocidadExtra;

    x += velocidadLateral;
    if (x <= limiteIzq || x + ancho >= limiteDer)
        velocidadLateral = -velocidadLateral;

    // Cambiar frame cada ~150ms (150/16 ≈ 9 frames)
    contadorFrame++;
    if (contadorFrame >= 9) {
        contadorFrame = 0;
        frameAnimacion = (frameAnimacion + 1) % 2;
        cargarFrameCiclista(frameAnimacion);
    }

    setPos(x, y);
}

void EnemigoCiclista::cargarFrameCiclista(int indice)
{
    if (hojaCiclista.isNull()) return;

    QPixmap frame = hojaCiclista.copy(554, 38, 175, 405);

    // Alternar reflejo horizontal (eje X) para simular pedaleo
    if (indice % 2 == 1)
        frame = frame.transformed(QTransform().scale(-1, 1)); // ← cambiar de (1,-1) a (-1,1)

    frame = frame.scaled(ancho, alto, Qt::IgnoreAspectRatio);
    setPixmap(frame);
}

void EnemigoCiclista::cargarFrame(int indice)
{
    cargarFrameCiclista(indice);
}

float EnemigoCiclista::obtenerX() const { return x; }
float EnemigoCiclista::obtenerY() const { return y; }
