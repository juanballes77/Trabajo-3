#include "nivel1.h"

Nivel1::Nivel1(QGraphicsScene *escena, QObject *parent)
    : NivelBase(escena, parent),
    temporizadorJuego(nullptr)
{
    temporizadorJuego = new QTimer(this);
    connect(temporizadorJuego, &QTimer::timeout, this, &Nivel1::actualizar);
}

Nivel1::~Nivel1()
{
    terminar();
}

// ─── Métodos virtuales ────────────────────────────────────────

void Nivel1::iniciar()
{
    escena->clear();

    // Fondo heredado de NivelBase, solo se pasa la ruta
    cargarFondo(":/fondo1.png");

    cargarJugador();
    cargarPlataformas();
    cargarEnemigos();

    temporizadorJuego->start(INTERVALO_JUEGO_MS);
}

void Nivel1::pausar()
{
    if (!estaPausado) {
        temporizadorJuego->stop();
        fondo->detener();
        estaPausado = true;
    }
}

void Nivel1::reanudar()
{
    if (estaPausado) {
        temporizadorJuego->start(INTERVALO_JUEGO_MS);
        fondo->iniciar();
        estaPausado = false;
    }
}

void Nivel1::terminar()
{
    if (temporizadorJuego && temporizadorJuego->isActive())
        temporizadorJuego->stop();

    if (fondo)
        fondo->detener();
}

// ─── Loop principal del nivel ─────────────────────────────────

void Nivel1::actualizar()
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

void Nivel1::cargarJugador()
{
    jugador = new Jugador();
    escena->addItem(jugador);
    jugador->establecerPosicion(100, 300);
    jugador->setZValue(1);
}

void Nivel1::cargarEnemigos()
{
    // Se implementará cuando creemos la clase Enemigo
}

void Nivel1::cargarPlataformas()
{
    // Se implementará cuando creemos la clase Plataforma
}

// ─── Detección ────────────────────────────────────────────────

void Nivel1::verificarColisiones()
{
    // Se implementará cuando tengamos enemigos y plataformas
}

void Nivel1::verificarMeta()
{
    // Se implementará cuando definamos la posición de la meta
    // Ejemplo: if (jugador->obtenerX() >= META_X)
    //              nivelCompletado = true;
}
