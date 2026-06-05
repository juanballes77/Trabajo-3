#include "nivel2.h"
#include <QGraphicsView>
#include <QBrush>
#include <QPen>
#include <cstdlib>
#include <ctime>

Nivel2::Nivel2(QGraphicsScene *escena, QObject *parent)
    : NivelBase(escena, parent),
    temporizadorJuego(nullptr),
    temporizadorObstaculos(nullptr),
    temporizadorEnemigos(nullptr),
    teclaIzquierda(false),
    teclaDerecha(false),
    teclaAcelerar(false),
    carreteraIzquierda(140.0f),
    carreteraDerecha(0.0f),
    velocidadScroll(6.0f),
    velocidadActual(6.0f),
    velocidadMaxima(20.0f),
    aceleracion(0.1f),
    desaceleracion(0.1f),
    repeticionesFondo(0),
    repeticionesParaMeta(2), // Meta aparece después de 10 repeticiones
    metaVisible(false),
    metaNivel2(nullptr)
{
    std::srand(std::time(nullptr));

    temporizadorJuego = new QTimer(this);
    connect(temporizadorJuego, &QTimer::timeout, this, &Nivel2::actualizar);

    temporizadorObstaculos = new QTimer(this);
    connect(temporizadorObstaculos, &QTimer::timeout, this, &Nivel2::generarObstaculo);

    temporizadorEnemigos = new QTimer(this);
    connect(temporizadorEnemigos, &QTimer::timeout, this, &Nivel2::generarEnemigo);

    // Constructor

}

Nivel2::~Nivel2()
{
    terminar();
}

// ─── Métodos virtuales ────────────────────────────────────────

void Nivel2::iniciar()
{
    escena->clear();
    obstaculos.clear();
    enemigos.clear();

    cargarFondoCarretera(":/road.png");
    cargarCarretera();
    cargarJugador();

    repeticionesFondo = 0;
    metaVisible = false;
    metaNivel2 = nullptr;

    temporizadorJuego->start(INTERVALO_JUEGO_MS);
    temporizadorObstaculos->start(INTERVALO_OBSTACULOS_MS);
    temporizadorEnemigos->start(INTERVALO_ENEMIGOS_MS);
}

void Nivel2::pausar()
{
    if (!estaPausado) {
        temporizadorJuego->stop();
        temporizadorObstaculos->stop();
        temporizadorEnemigos->stop();
        estaPausado = true;
    }
}

void Nivel2::reanudar()
{
    if (estaPausado) {
        temporizadorJuego->start(INTERVALO_JUEGO_MS);
        temporizadorObstaculos->start(INTERVALO_OBSTACULOS_MS);
        temporizadorEnemigos->start(INTERVALO_ENEMIGOS_MS);
        estaPausado = false;
    }
}

void Nivel2::terminar()
{
    if (temporizadorJuego && temporizadorJuego->isActive())
        temporizadorJuego->stop();
    if (temporizadorObstaculos && temporizadorObstaculos->isActive())
        temporizadorObstaculos->stop();
    if (temporizadorEnemigos && temporizadorEnemigos->isActive())
        temporizadorEnemigos->stop();
}

// ─── Loop principal ───────────────────────────────────────────

void Nivel2::actualizar()
{
    if (!jugador)
        return;

    // MUA: acelerar o desacelerar según tecla espacio
    if (teclaAcelerar) {
        if (velocidadActual < velocidadMaxima)
            velocidadActual += aceleracion;
    } else {
        if (velocidadActual > velocidadScroll)
            velocidadActual -= desaceleracion;
    }

    // Detectar repetición del fondo
    static float yAnterior = 0;
    if (fondoCarretera1) {
        float yActual = fondoCarretera1->y();
        if (yActual < yAnterior && !metaVisible) { // Detecta cuando se reinicia (salta hacia arriba)
            repeticionesFondo++;
            if (repeticionesFondo >= repeticionesParaMeta)
                mostrarMeta();
        }
        yAnterior = yActual;
    }

    // Mover meta con el fondo
    if (metaVisible && metaNivel2) {
        metaNivel2->moveBy(0, velocidadActual);
    }


    procesarMovimiento();
    desplazarFondoCarretera(velocidadActual);
    actualizarEnemigos();
    actualizarObstaculos();
    limpiarElementosFueraDePantalla();
    liminarJugadorEnCarretera();
    jugador->actualizar();
    verificarColisiones();
    verificarMeta();
    verificarEstado();
    actualizarHUD();
}

// ─── Teclado ──────────────────────────────────────────────────

void Nivel2::teclaPresionada(QKeyEvent *evento)
{
    switch (evento->key()) {
    case Qt::Key_A:     teclaIzquierda = true;  break;
    case Qt::Key_D:     teclaDerecha   = true;  break;
    case Qt::Key_Space: teclaAcelerar  = true;  break;
    default: break;
    }
}

void Nivel2::teclaLiberada(QKeyEvent *evento)
{
    switch (evento->key()) {
    case Qt::Key_A:     teclaIzquierda = false; break;
    case Qt::Key_D:     teclaDerecha   = false; break;
    case Qt::Key_Space: teclaAcelerar  = false; break;
    default: break;
    }
}

// ─── Movimiento ───────────────────────────────────────────────

void Nivel2::procesarMovimiento()
{
    if (teclaIzquierda) jugador->moverIzquierda();
    if (teclaDerecha)   jugador->moverDerecha();
}

void Nivel2::liminarJugadorEnCarretera()
{
    float nx           = jugador->obtenerX();
    float anchoJugador = jugador->boundingRect().width();

    if (nx < carreteraIzquierda)
        jugador->establecerPosicion(carreteraIzquierda, jugador->obtenerY());
    else if (nx + anchoJugador > carreteraDerecha)
        jugador->establecerPosicion(carreteraDerecha - anchoJugador, jugador->obtenerY());
}

// ─── Generación esporádica ────────────────────────────────────

void Nivel2::generarObstaculo()
{
    int cantidad = 1 + (std::rand() % 6);

    for (int i = 0; i < cantidad; i++) {
        float rangoX = carreteraDerecha - carreteraIzquierda - 60;
        float x      = carreteraIzquierda + (std::rand() % (int)rangoX);

        // Espaciado mínimo de 150px entre obstáculos
        Obstaculo *obs = new Obstaculo(x, -50 - (i * 150), 60, 30);
        escena->addItem(obs);
        obstaculos.append(obs);
    }

    temporizadorObstaculos->start(1000 + (std::rand() % 10));
}

void Nivel2::generarEnemigo()
{
    int cantidad = 1 + (std::rand() % 4);

    for (int i = 0; i < cantidad; i++) {
        float rangoX = carreteraDerecha - carreteraIzquierda - 50;
        float x      = carreteraIzquierda + (std::rand() % (int)rangoX);

        EnemigoCiclista *enemigo = new EnemigoCiclista(x, -80 - (i * 100), 50, 80);
        escena->addItem(enemigo);
        enemigos.append(enemigo);
    }

    // Intervalo aleatorio entre 1.5 y 4 segundos
    temporizadorEnemigos->start(1500 + (std::rand() % 2500));
}
// ─── Actualización de elementos ───────────────────────────────

void Nivel2::actualizarObstaculos()
{
    for (Obstaculo *obs : obstaculos)
        obs->moveBy(0, velocidadActual); // ← atributo de la clase
}
void Nivel2::actualizarEnemigos()
{
    for (EnemigoCiclista *enemigo : enemigos)
        enemigo->actualizar(velocidadActual, carreteraIzquierda, carreteraDerecha); // ← atributo de la clase
}

void Nivel2::limpiarElementosFueraDePantalla()
{
    float altoEscena = escena->sceneRect().height();

    for (int i = obstaculos.size() - 1; i >= 0; i--) {
        float yObstaculo = obstaculos[i]->mapToScene(obstaculos[i]->rect().bottomLeft()).y();
        if (yObstaculo > altoEscena) {
            escena->removeItem(obstaculos[i]);
            delete obstaculos[i];
            obstaculos.removeAt(i);
        }
    }

    for (int i = enemigos.size() - 1; i >= 0; i--) {
        float yEnemigo = enemigos[i]->mapToScene(enemigos[i]->rect().bottomLeft()).y();
        if (yEnemigo > altoEscena) {
            escena->removeItem(enemigos[i]);
            delete enemigos[i];
            enemigos.removeAt(i);
        }
    }
}

// ─── Carga de elementos ───────────────────────────────────────

void Nivel2::cargarCarretera()
{
    QRectF rect        = escena->sceneRect();
    carreteraIzquierda = 140;
    carreteraDerecha   = rect.width() - 140;
}

void Nivel2::cargarJugador()
{
    jugador = new Jugador();
    escena->addItem(jugador);

    QRectF rect    = escena->sceneRect();
    float xInicial = rect.width()  / 2.0f;
    float yInicial = rect.height() * 0.75f;
    jugador->establecerPosicion(xInicial, yInicial);
    jugador->establecerGravedad(false);
    jugador->setZValue(1);
}

void Nivel2::cargarEnemigos()
{
    // Los enemigos se generan esporádicamente con temporizadorEnemigos
}

// ─── Detección de colisiones ──────────────────────────────────

void Nivel2::verificarColisiones()
{
    QList<QGraphicsItem*> colisiones = jugador->collidingItems();

    for (QGraphicsItem *item : colisiones) {
        if (dynamic_cast<Obstaculo*>(item) || dynamic_cast<EnemigoCiclista*>(item)) {
            velocidadActual = velocidadScroll * 0.5f;
            return;
        }
    }

    // Recuperar velocidad normal gradualmente
    if (!teclaAcelerar && velocidadActual < velocidadScroll)
        velocidadActual += aceleracion;
}


void Nivel2::mostrarMeta()
{
    metaVisible = true;

    metaNivel2 = new QGraphicsRectItem(carreteraIzquierda, 0,
                                       carreteraDerecha - carreteraIzquierda, 20);
    metaNivel2->setBrush(QBrush(QColor(255, 215, 0)));
    metaNivel2->setPen(QPen(QColor(255, 255, 255), 3));
    metaNivel2->setZValue(2);
    escena->addItem(metaNivel2);
}
void Nivel2::verificarMeta()
{
    if (!metaVisible || !metaNivel2 || !jugador)
        return;

    if (jugador->collidesWithItem(metaNivel2)) {
        nivelCompletado = true;
        temporizadorJuego->stop();
        emit nivelTerminado();
    }
}
