#include "nivel2.h"

Nivel2::Nivel2(QGraphicsScene *escena, QObject *parent)
    : NivelBase(escena, parent),
    temporizadorJuego(nullptr)
{
    temporizadorJuego = new QTimer(this);
    connect(temporizadorJuego, &QTimer::timeout, this, &Nivel2::actualizar);
}

Nivel2::~Nivel2()
{
    terminar();
}

// ─── Métodos virtuales ────────────────────────────────────────

void Nivel2::iniciar()
{
    escena->clear();

    // Fondo heredado de NivelBase, solo se pasa la ruta
    cargarFondo(":/fondo2.png");

    cargarJugador();
    cargarPlataformas();
    cargarEnemigos();

    temporizadorJuego->start(INTERVALO_JUEGO_MS);
}

void Nivel2::pausar()
{
    if (!estaPausado) {
        temporizadorJuego->stop();
        fondo->detener();
        estaPausado = true;
    }
}

void Nivel2::reanudar()
{
    if (estaPausado) {
        temporizadorJuego->start(INTERVALO_JUEGO_MS);
        fondo->iniciar();
        estaPausado = false;
    }
}

void Nivel2::terminar()
{
    if (temporizadorJuego && temporizadorJuego->isActive())
        temporizadorJuego->stop();

    if (fondo)
        fondo->detener();
}

// ─── Loop principal del nivel ─────────────────────────────────

void Nivel2::actualizar()
{
    if (!jugador)
        return;

    jugador->actualizar();
    verificarColisiones();
    verificarMeta();
    verificarEstado();
    actualizarHUD();
}

// ─── Carga de elementos ───────────────────────────────────────

void Nivel2::cargarJugador()
{
    jugador = new Jugador();
    escena->addItem(jugador);
    jugador->establecerPosicion(100, 300);
    jugador->setZValue(1);
}

void Nivel2::cargarEnemigos()
{
    // Se implementará cuando se defina la temática del nivel 2
}

void Nivel2::cargarPlataformas()
{
    // Se implementará cuando se defina la temática del nivel 2.
}

// ─── Detección ────────────────────────────────────────────────

void Nivel2::verificarColisiones()
{
    // Se implementará cuando tengamos enemigos y plataformas
}

void Nivel2::verificarMeta()
{
    // Se implementará cuando definamos la posición de la meta
}
