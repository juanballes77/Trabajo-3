#include "fondo.h"

Fondo::Fondo(const QString &rutaImagen, QObject *parent)
    : QObject(parent),
    QGraphicsPixmapItem(),
    frameActual(0),
    totalFrames(4)
{
    hoja = QPixmap(rutaImagen);

    temporizador = new QTimer(this);
    connect(temporizador, &QTimer::timeout, this, &Fondo::siguienteFrame);

    cargarFrame(0);
}

Fondo::~Fondo()
{
    detener();
}

// ─── Control de animación ─────────────────────────────────────

void Fondo::iniciar()
{
    temporizador->start(INTERVALO_MS);
}

void Fondo::detener()
{
    if (temporizador->isActive())
        temporizador->stop();
}

// ─── Slot: avanzar al siguiente frame ─────────────────────────

void Fondo::siguienteFrame()
{
    frameActual = (frameActual + 1) % totalFrames;
    cargarFrame(frameActual);
}

// ─── Recortar frame avanzando en X ───────────────────────────

void Fondo::cargarFrame(int indice)
{
    if (hoja.isNull())
        return;

    int x = FRAME_X + (indice * FRAME_PASO);

    QPixmap frame = hoja.copy(x, FRAME_Y, FRAME_ANCHO, FRAME_ALTO);
    setPixmap(frame);
}
