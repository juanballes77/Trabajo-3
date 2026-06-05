#include "jugador.h"

Jugador::Jugador(QObject *parent)
    : QObject(parent),
    QGraphicsPixmapItem(),
    x(0.0f),
    y(0.0f),
    velocidadX(0.0f),
    velocidadY(0.0f),
    velocidad(5.0f),
    fuerzaSalto(-15.0f),
    gravedad(0.8f),
    estaEnSuelo(false),
    estaVivo(true)
{}

// ─── Movimiento ───────────────────────────────────────────────

void Jugador::moverIzquierda()
{
    velocidadX = -velocidad;
}

void Jugador::moverDerecha()
{
    velocidadX = velocidad;
}

void Jugador::saltar()
{
    if (estaEnSuelo) {
        velocidadY = fuerzaSalto;
        estaEnSuelo = false;
    }
}

// ─── Física ───────────────────────────────────────────────────

void Jugador::aplicarGravedad()
{
    velocidadY += gravedad;
}

void Jugador::actualizar()
{
    aplicarGravedad();

    x += velocidadX;
    y += velocidadY;

    // Actualizar posición visual en la escena
    setPos(x, y);

    // Resetear velocidad horizontal (el jugador solo se mueve si se presiona tecla)
    velocidadX = 0.0f;
}

// ─── Getters ──────────────────────────────────────────────────

float Jugador::obtenerX() const
{
    return x;
}

float Jugador::obtenerY() const
{
    return y;
}

bool Jugador::obtenerEstaVivo() const
{
    return estaVivo;
}

bool Jugador::obtenerEstaEnSuelo() const
{
    return estaEnSuelo;
}

// ─── Setters ──────────────────────────────────────────────────

void Jugador::establecerPosicion(float x, float y)
{
    this->x = x;
    this->y = y;
    setPos(this->x, this->y);
}

void Jugador::establecerEstaEnSuelo(bool estado)
{
    estaEnSuelo = estado;
}

void Jugador::establecerEstaVivo(bool estado)
{
    estaVivo = estado;
}
