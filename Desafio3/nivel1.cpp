#include "nivel1.h"
#include <algorithm>
#include <QGraphicsView>
#include <QTransform>

Nivel1::Nivel1(QGraphicsScene *escena, QObject *parent)
    : NivelBase(escena, parent),
    temporizadorJuego(nullptr),
    teclaIzquierda(false),
    teclaDerecha(false),
    teclaImpulso(false),
    velocidadJugador(VELOCIDAD_NORMAL),
    metaNivel(nullptr),
    calamar(nullptr),
    altoEscena(0)
{
    temporizadorJuego = new QTimer(this);
    connect(temporizadorJuego, &QTimer::timeout, this, &Nivel1::actualizar);
}

Nivel1::~Nivel1()
{
    terminar();
}

void Nivel1::iniciar()
{
    if (temporizadorParallax && temporizadorParallax->isActive())
        temporizadorParallax->stop();

    copiasParallax.clear();
    escena->clear();

    obstaculos.clear();
    tiburones.clear();
    cangrejos.clear();
    metaNivel        = nullptr;
    calamar          = nullptr;
    altoEscena       = escena->sceneRect().height();
    velocidadJugador = VELOCIDAD_NORMAL;

    cargarFondoParallax(":/fondo1.png");
    cargarJugador();
    cargarObstaculos();
    cargarEnemigos();
    cargarMeta();

    temporizadorJuego->start(INTERVALO_JUEGO_MS);
}

void Nivel1::pausar()
{
    if (!estaPausado) {
        temporizadorJuego->stop();
        estaPausado = true;
    }
}

void Nivel1::reanudar()
{
    if (estaPausado) {
        temporizadorJuego->start(INTERVALO_JUEGO_MS);
        estaPausado = false;
    }
}

void Nivel1::terminar()
{
    if (temporizadorJuego && temporizadorJuego->isActive())
        temporizadorJuego->stop();

    if (temporizadorParallax) {
        temporizadorParallax->stop();
        temporizadorParallax->disconnect();
    }

    copiasParallax.clear();
}

void Nivel1::actualizar()
{
    if (!jugador) return;

    procesarMovimiento();
    jugador->actualizar();
    actualizarEnemigos();

    if (!escena->views().isEmpty()) {
        QGraphicsView *vista = escena->views().first();
        QPointF centroActual  = vista->mapToScene(vista->viewport()->rect().center());
        QPointF centroJugador = QPointF(jugador->obtenerX(), jugador->obtenerY());
        QPointF nuevoCentro   = centroActual + (centroJugador - centroActual) * 0.15;
        vista->centerOn(nuevoCentro);
    }

    desplazarFondoParallax(jugador->obtenerX());
    verificarColisiones();
    verificarMeta();
    verificarEstado();
}

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

void Nivel1::procesarMovimiento()
{
    jugador->establecerVelocidad(velocidadJugador);
    if (teclaIzquierda) jugador->moverIzquierda();
    if (teclaDerecha)   jugador->moverDerecha();
    if (teclaImpulso)   jugador->impulsarse();
}

void Nivel1::actualizarEnemigos()
{
    for (Tiburon *t : tiburones)
        t->actualizar();
    for (Cangrejo *c : cangrejos)
        c->actualizar();

    if (calamar) {
        if (jugador->obtenerX() >= 7700)
            calamar->establecerObjetivo(jugador->obtenerX(), jugador->obtenerY());
        calamar->actualizar();
    }
}

void Nivel1::cargarJugador()
{
    jugador = new Jugador();
    escena->addItem(jugador);
    jugador->establecerPosicion(100, 300);
    jugador->establecerLimites(altoEscena);
    jugador->setZValue(1);
}

void Nivel1::cargarObstaculos()
{
    QVector<QRectF> terreno = {
                               {300,   0,              100, 500            },
                               {1000,  altoEscena-400, 80,  400            },
                               {1800,  0,              80,  80             },
                               {1800,  150,            80,  altoEscena-150 },
                               {2400,  500,            100, altoEscena-500 },
                               {3200,  0,              80,  350            },
                               {3900,  altoEscena-300, 100, 300            },
                               {4500,  0,              80,  200            },
                               {4500,  400,            80,  altoEscena-400 },
                               {5500,  altoEscena-350, 100, 350            },
                               {6200,  0,              80,  300            },
                               {7000,  200,            80,  altoEscena-200 },
                               {7500,  200,            80,  altoEscena-200 },
                               };

    for (const QRectF &def : terreno) {
        Obstaculo *obs = new Obstaculo(def.x(), def.y(), def.width(), def.height());
        escena->addItem(obs);
        obstaculos.append(obs);
    }

    QGraphicsRectItem *suelo = new QGraphicsRectItem(0, altoEscena - 20,
                                                     escena->sceneRect().width(), 20);
    suelo->setBrush(QBrush(QColor(80, 50, 20)));
    suelo->setPen(Qt::NoPen);
    suelo->setZValue(0);
    escena->addItem(suelo);
}

void Nivel1::cargarEnemigos()
{
    QVector<QVector<float>> posTiburones = {
                                            {500,  200, 400,  800 },
                                            {1200, 30,  1000, 1600},
                                            {2200, 200, 2200, 2800},
                                            {3500, 250, 3300, 4300},
                                            {4700, 200, 4600, 5200},
                                            {5800, 300, 5700, 6700},
                                            {6600, 300, 5700, 6700},
                                            {6500, 70,  6700, 7450},
                                            {8000, 200, 7800, 8500},
                                            };

    for (const QVector<float> &p : posTiburones) {
        Tiburon *t = new Tiburon(p[0], p[1], p[2], p[3]);
        escena->addItem(t);
        tiburones.append(t);
    }

    QVector<QVector<float>> posCangrejos = {
                                            {700,  altoEscena-100, 500,  800 },
                                            {2800, altoEscena-100, 2600, 3700},
                                            {4000, altoEscena-100, 2600, 3700},
                                            {5800, altoEscena-100, 5600, 6600},
                                            {6800, altoEscena-100, 5600, 6400},
                                            {8500, altoEscena-100, 8300, 9000},
                                            };

    for (const QVector<float> &p : posCangrejos) {
        Cangrejo *c = new Cangrejo(p[0], p[1], p[2], p[3]);
        escena->addItem(c);
        cangrejos.append(c);
    }

    calamar = new Calamar(8500, 300);
    escena->addItem(calamar);
}

void Nivel1::cargarMeta()
{
    QPixmap hoja(":/meta.png");
    QPixmap imagenMeta = hoja.copy(4, 285, 197, 19);

    QTransform rotacion;
    rotacion.rotate(90);
    imagenMeta = imagenMeta.transformed(rotacion);
    imagenMeta = imagenMeta.scaled(imagenMeta.width(), altoEscena, Qt::IgnoreAspectRatio);

    metaNivel = new Meta(LONGITUD_NIVEL - 150, 0, imagenMeta.width(), altoEscena);
    escena->addItem(metaNivel);
    metaNivel->setZValue(0);

    QGraphicsPixmapItem *imgMeta = new QGraphicsPixmapItem(imagenMeta);
    imgMeta->setPos(LONGITUD_NIVEL - 150, 0);
    imgMeta->setZValue(1);
    escena->addItem(imgMeta);
}

void Nivel1::verificarColisiones()
{
    QList<QGraphicsItem*> colisiones = jugador->collidingItems();
    bool colisionEnemigo = false;

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

        if (dynamic_cast<Tiburon*>(item) || dynamic_cast<Cangrejo*>(item))
            colisionEnemigo = true;

        // Calamar → solo empuja hacia atrás
        if (dynamic_cast<Calamar*>(item)) {
            float nx = jugador->obtenerX() - 80.0f;
            if (nx < 0) nx = 0;
            jugador->establecerPosicion(nx, jugador->obtenerY());
        }
    }

    if (colisionEnemigo)
        velocidadJugador = VELOCIDAD_REDUCIDA;
    else if (velocidadJugador < VELOCIDAD_NORMAL)
        velocidadJugador += 0.05f;
}

void Nivel1::verificarMeta()
{
    if (!metaNivel || !jugador) return;

    if (jugador->collidesWithItem(metaNivel)) {
        nivelCompletado = true;
        temporizadorJuego->stop();
        emit nivelTerminado();
    }
}
