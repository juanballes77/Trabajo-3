#include "enemigo.h"

Enemigo::Enemigo(float x, float y, float limiteIzq, float limiteDer,
                 float velocidad, QObject *parent)
    : QObject(parent),
    QGraphicsPixmapItem(),
    x(x),
    y(y),
    velocidad(velocidad),
    limiteIzquierdo(limiteIzq),
    limiteDerecho(limiteDer),
    direccion(1.0f),
    estaVivo(true),
    frameActual(0),
    mirandoDerecha(true)
{
    temporizadorAnimacion = new QTimer(this);
    connect(temporizadorAnimacion, &QTimer::timeout, this, &Enemigo::onSiguienteFrame);
    temporizadorAnimacion->start(150);
}

Enemigo::~Enemigo()
{
    temporizadorAnimacion->stop();
}

// ─── Patrulla de lado a lado ──────────────────────────────────

void Enemigo::patrullar()
{
    x += velocidad * direccion;

    // Rebotar en los límites
    if (x >= limiteDerecho) {
        direccion    = -1.0f;
        mirandoDerecha = false;
    } else if (x <= limiteIzquierdo) {
        direccion    = 1.0f;
        mirandoDerecha = true;
    }

    setPos(x, y);
}

void Enemigo::onSiguienteFrame()
{
    if (!frames.isEmpty()) {
        frameActual = (frameActual + 1) % frames.size();
        cargarFrame(frameActual);
    }
}

// ─── Getters / Setters ────────────────────────────────────────

float Enemigo::obtenerX() const { return x; }
float Enemigo::obtenerY() const { return y; }
bool  Enemigo::obtenerEstaVivo() const { return estaVivo; }
void  Enemigo::establecerEstaVivo(bool estado) { estaVivo = estado; }
