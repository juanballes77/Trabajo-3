#include "nivel1.h"
#include <algorithm>
#include <QGraphicsView>

Nivel1::Nivel1(QGraphicsScene *escena, QObject *parent)
    : NivelBase(escena, parent),
    temporizadorJuego(nullptr),
    teclaIzquierda(false),
    teclaDerecha(false),
    teclaImpulso(false),
    metaNivel(nullptr)
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
    obstaculos.clear();
    metaNivel = nullptr;

    cargarFondo(":/fondo1.png");
    cargarJugador();
    cargarObstaculos();
    cargarMeta();
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

// ─── Loop principal ───────────────────────────────────────────

void Nivel1::actualizar()
{
    if (!jugador)
        return;

    procesarMovimiento();
    jugador->actualizar();

    // Cámara sigue al jugador
    if (!escena->views().isEmpty())
        escena->views().first()->centerOn(jugador);

    verificarColisiones();
    verificarMeta();
    verificarEstado();
    actualizarHUD();
}

// ─── Teclado ──────────────────────────────────────────────────

void Nivel1::teclaPresionada(QKeyEvent *evento)
{
    switch (evento->key()) {
    case Qt::Key_A:     teclaIzquierda = true;  break;
    case Qt::Key_D:     teclaDerecha   = true;  break;
    case Qt::Key_Space: teclaImpulso   = true;  break;
    default: break;
    }
}

void Nivel1::teclaLiberada(QKeyEvent *evento)
{
    switch (evento->key()) {
    case Qt::Key_A:     teclaIzquierda = false; break;
    case Qt::Key_D:     teclaDerecha   = false; break;
    case Qt::Key_Space: teclaImpulso   = false; break;
    default: break;
    }
}

// ─── Movimiento ───────────────────────────────────────────────

void Nivel1::procesarMovimiento()
{
    if (teclaIzquierda) jugador->moverIzquierda();
    if (teclaDerecha)   jugador->moverDerecha();
    if (teclaImpulso)   jugador->impulsarse();
}

// ─── Carga de elementos ───────────────────────────────────────

void Nivel1::cargarJugador()
{
    jugador = new Jugador();
    escena->addItem(jugador);
    jugador->establecerPosicion(100, 300);
    jugador->setZValue(1);
}

void Nivel1::cargarObstaculos()
{
    QVector<QRectF> definiciones = {
                                    {200,  400, 150, 30},
                                    {450,  300, 30,  120},
                                    {700,  450, 200, 30},
                                    {950,  250, 30,  150},
                                    {1150, 380, 180, 30},
                                    };

    for (const QRectF &def : definiciones) {
        Obstaculo *obs = new Obstaculo(def.x(), def.y(), def.width(), def.height());
        escena->addItem(obs);
        obstaculos.append(obs);
    }
}

void Nivel1::cargarMeta()
{
    // Meta al final del nivel, ocupa todo el alto de la escena
    float altoEscena = escena->sceneRect().height();
    metaNivel = new Meta(LONGITUD_NIVEL - 150, 0, 100, altoEscena);
    escena->addItem(metaNivel);
    metaNivel->setZValue(0);
}

void Nivel1::cargarEnemigos()
{
    // Se implementará cuando creemos la clase Enemigo
}

// ─── Detección de colisiones ──────────────────────────────────

void Nivel1::verificarColisiones()
{
    QList<QGraphicsItem*> colisiones = jugador->collidingItems();

    for (QGraphicsItem *item : colisiones) {
        if (dynamic_cast<Obstaculo*>(item)) {
            QRectF rectJugador   = jugador->boundingRect().translated(jugador->pos());
            QRectF rectObstaculo = item->boundingRect().translated(item->pos());

            float solapIzq = rectObstaculo.right()  - rectJugador.left();
            float solapDer = rectJugador.right()     - rectObstaculo.left();
            float solapArr = rectObstaculo.bottom()  - rectJugador.top();
            float solapAba = rectJugador.bottom()    - rectObstaculo.top();

            float minSolap = std::min({solapIzq, solapDer, solapArr, solapAba});

            float nx = jugador->obtenerX();
            float ny = jugador->obtenerY();

            if (minSolap == solapIzq)      nx += solapIzq;
            else if (minSolap == solapDer) nx -= solapDer;
            else if (minSolap == solapArr) ny += solapArr;
            else                           ny -= solapAba;

            jugador->establecerPosicion(nx, ny);
        }
    }
}

void Nivel1::verificarMeta()
{
    if (!metaNivel || !jugador)
        return;

    // Si el jugador toca la meta, emitir señal de nivel terminado
    if (jugador->collidesWithItem(metaNivel)) {
        nivelCompletado = true;
        temporizadorJuego->stop();
        emit nivelTerminado();
    }
}
