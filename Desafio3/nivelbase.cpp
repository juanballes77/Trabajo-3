#include "nivelbase.h"
#include <QTransform>

NivelBase::NivelBase(QGraphicsScene *escena, QObject *parent)
    : QObject(parent),
    escena(escena),
    jugador(nullptr),
    fondo(nullptr),
    puntaje(0),
    vidasRestantes(3),
    nivelCompletado(false),
    estaPausado(false)
{}

NivelBase::~NivelBase()
{
    delete jugador;
    delete fondo;
}

// ─── Métodos comunes ──────────────────────────────────────────

void NivelBase::cargarFondo(const QString &rutaImagen)
{
    fondo = new Fondo(rutaImagen);
    escena->addItem(fondo);
    fondo->setPos(0, 0);
    fondo->setZValue(-1);

    // Escalar el fondo para que ocupe toda la escena
    QRectF rect = escena->sceneRect();
    double escalaX = rect.width()  / fondo->pixmap().width();
    double escalaY = rect.height() / fondo->pixmap().height();
    fondo->setTransform(QTransform::fromScale(escalaX, escalaY));

    fondo->iniciar();
}

void NivelBase::actualizarHUD()
{
    // Se implementará cuando tengamos la interfaz gráfica (HUD)
}

void NivelBase::verificarEstado()
{
    if (!jugador)
        return;

    if (!jugador->obtenerEstaVivo()) {
        perderVida();

        if (vidasRestantes <= 0)
            emit juegoTerminado();
        else
            iniciar();
    }

    if (nivelCompletado)
        emit nivelTerminado();
}

void NivelBase::agregarPuntaje(int cantidad)
{
    puntaje += cantidad;
    actualizarHUD();
}

void NivelBase::perderVida()
{
    vidasRestantes--;
    actualizarHUD();
}

// ─── Getters ──────────────────────────────────────────────────

int NivelBase::obtenerPuntaje() const
{
    return puntaje;
}

int NivelBase::obtenerVidasRestantes() const
{
    return vidasRestantes;
}

bool NivelBase::obtenerNivelCompletado() const
{
    return nivelCompletado;
}
