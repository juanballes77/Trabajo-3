#include "nivelbase.h"

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
    fondo->setZValue(-1); // Siempre detrás de los demás elementos
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

    // Si el jugador murió
    if (!jugador->obtenerEstaVivo()) {
        perderVida();

        if (vidasRestantes <= 0)
            emit juegoTerminado();
        else
            iniciar(); // Reiniciar el nivel con una vida menos
    }

    // Si el nivel fue completado
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
