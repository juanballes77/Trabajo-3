#include "obstaculo.h"
#include <QBrush>
#include <QPen>

Obstaculo::Obstaculo(float x, float y, float ancho, float alto, QObject *parent)
    : QObject(parent),
    QGraphicsRectItem(x, y, ancho, alto),
    x(x),
    y(y),
    ancho(ancho),
    alto(alto)
{
    // Color temporal: azul oscuro con borde celeste (temática submarina)
    setBrush(QBrush(QColor(20, 60, 100)));
    setPen(QPen(QColor(0, 180, 220), 2));

    setZValue(0); // Entre el fondo (-1) y el jugador (1)
}

// ─── Getters ──────────────────────────────────────────────────

float Obstaculo::obtenerX()     const { return x; }
float Obstaculo::obtenerY()     const { return y; }
float Obstaculo::obtenerAncho() const { return ancho; }
float Obstaculo::obtenerAlto()  const { return alto; }
