#include "nivelbase.h"
#include <QTransform>
#include <QPixmap>

NivelBase::NivelBase(QGraphicsScene *escena, QObject *parent)
    : QObject(parent),
    escena(escena),
    jugador(nullptr),
    fondo(nullptr),
    fondoCarretera1(nullptr),
    fondoCarretera2(nullptr),
    fondoCarretera3(nullptr),
    fondoCarretera4(nullptr),
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

// ─── Fondo animado (nivel 1) ──────────────────────────────────

void NivelBase::cargarFondo(const QString &rutaImagen)
{
    fondo = new Fondo(rutaImagen);
    escena->addItem(fondo);
    fondo->setPos(0, 0);
    fondo->setZValue(-1);

    QRectF rect    = escena->sceneRect();
    double escalaX = rect.width()  / fondo->pixmap().width();
    double escalaY = rect.height() / fondo->pixmap().height();
    fondo->setTransform(QTransform::fromScale(escalaX, escalaY));

    fondo->iniciar();
}

// ─── Fondo carretera (nivel 2) ────────────────────────────────

void NivelBase::cargarFondoCarretera(const QString &rutaImagen)
{
    QPixmap mitadIzq(rutaImagen);
    QPixmap mitadDer = mitadIzq.transformed(QTransform().scale(-1, 1));

    QRectF rect       = escena->sceneRect();
    float anchoMitad  = rect.width() / 2.0f;
    float altoVista   = rect.height();

    // Escalar para que ocupe exactamente la mitad del ancho y todo el alto
    mitadIzq = mitadIzq.scaled(anchoMitad, altoVista, Qt::IgnoreAspectRatio);
    mitadDer = mitadDer.scaled(anchoMitad, altoVista, Qt::IgnoreAspectRatio);

    // Copia A — empieza en Y=0 (visible)
    fondoCarretera1 = new QGraphicsPixmapItem(mitadIzq);
    fondoCarretera2 = new QGraphicsPixmapItem(mitadDer);
    fondoCarretera1->setPos(0,          0);
    fondoCarretera2->setPos(anchoMitad, 0);
    fondoCarretera1->setZValue(-1);
    fondoCarretera2->setZValue(-1);
    escena->addItem(fondoCarretera1);
    escena->addItem(fondoCarretera2);

    // Copia B — empieza en Y=-altoVista (arriba, lista para entrar)
    fondoCarretera3 = new QGraphicsPixmapItem(mitadIzq);
    fondoCarretera4 = new QGraphicsPixmapItem(mitadDer);
    fondoCarretera3->setPos(0,          -altoVista);
    fondoCarretera4->setPos(anchoMitad, -altoVista);
    fondoCarretera3->setZValue(-1);
    fondoCarretera4->setZValue(-1);
    escena->addItem(fondoCarretera3);
    escena->addItem(fondoCarretera4);
}

void NivelBase::desplazarFondoCarretera(float velocidad)
{
    if (!fondoCarretera1 || !fondoCarretera2 || !fondoCarretera3 || !fondoCarretera4)
        return;

    float altoVista = escena->sceneRect().height();

    // Mover las 4 piezas hacia abajo
    fondoCarretera1->setY(fondoCarretera1->y() + velocidad);
    fondoCarretera2->setY(fondoCarretera2->y() + velocidad);
    fondoCarretera3->setY(fondoCarretera3->y() + velocidad);
    fondoCarretera4->setY(fondoCarretera4->y() + velocidad);

    // Cuando la copia A sale por abajo, sube al tope
    if (fondoCarretera1->y() >= altoVista) {
        fondoCarretera1->setY(fondoCarretera3->y() - altoVista);
        fondoCarretera2->setY(fondoCarretera4->y() - altoVista);
    }

    // Cuando la copia B sale por abajo, sube al tope
    if (fondoCarretera3->y() >= altoVista) {
        fondoCarretera3->setY(fondoCarretera1->y() - altoVista);
        fondoCarretera4->setY(fondoCarretera2->y() - altoVista);
    }
}

// ─── Métodos comunes ──────────────────────────────────────────

void NivelBase::actualizarHUD()
{
    // Se implementará cuando tengamos el HUD
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

int  NivelBase::obtenerPuntaje()         const { return puntaje; }
int  NivelBase::obtenerVidasRestantes()  const { return vidasRestantes; }
bool NivelBase::obtenerNivelCompletado() const { return nivelCompletado; }
