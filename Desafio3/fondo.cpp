#include "fondo.h"

Fondo::Fondo(const QString &rutaImagen, QObject *parent)
    : QObject(parent),
    QGraphicsPixmapItem(),
    frameActual(0),
    totalFrames(4)
{
    // Cargar el spritesheet completo
    hoja = QPixmap(rutaImagen);

    // Crear y configurar el temporizador
    temporizador = new QTimer(this);
    connect(temporizador, &QTimer::timeout, this, &Fondo::siguienteFrame);

    // Mostrar el primer frame al crear el objeto
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

// ─── Recortar y aplicar el frame del spritesheet ──────────────

void Fondo::cargarFrame(int indice)
{
    if (hoja.isNull())
        return;

    int y = FRAME_Y_BASE + (indice * FRAME_PASO);

    QPixmap frame = hoja.copy(FRAME_X, y, FRAME_ANCHO, FRAME_ALTO);
    setPixmap(frame);
}
