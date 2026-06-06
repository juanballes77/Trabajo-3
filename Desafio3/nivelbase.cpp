#include "nivelbase.h"
#include <QTransform>
#include <QPixmap>

NivelBase::NivelBase(QGraphicsScene *escena, QObject *parent)
    : QObject(parent),
    escena(escena),
    jugador(nullptr),
    temporizadorParallax(nullptr),
    frameParallaxActual(0),
    fondoCarretera1(nullptr),
    fondoCarretera2(nullptr),
    fondoCarretera3(nullptr),
    fondoCarretera4(nullptr),
    nivelCompletado(false),
    estaPausado(false)
{}

NivelBase::~NivelBase()
{
    delete jugador;
}

// ─── Fondo parallax horizontal (nivel 1) ─────────────────────

void NivelBase::cargarFondoParallax(const QString &rutaImagen)
{
    if (temporizadorParallax) {
        temporizadorParallax->stop();
        temporizadorParallax->disconnect();
        delete temporizadorParallax;
        temporizadorParallax = nullptr;
    }

    hojaParallax        = QPixmap(rutaImagen);
    frameParallaxActual = 0;
    copiasParallax.clear();

    QPixmap imagen = hojaParallax.copy(7, 18, 511, 431);
    QRectF  rect   = escena->sceneRect();
    float   escala = rect.height() / imagen.height();
    int nuevoAncho = imagen.width() * escala;
    imagen = imagen.scaled(nuevoAncho, rect.height(), Qt::IgnoreAspectRatio);

    for (int i = 0; i < 16; i++) {
        QGraphicsPixmapItem *copia = new QGraphicsPixmapItem(imagen);
        copia->setPos(nuevoAncho * i, 0);
        copia->setZValue(-1);
        escena->addItem(copia);
        copiasParallax.append(copia);
    }

    temporizadorParallax = new QTimer(this);
    connect(temporizadorParallax, &QTimer::timeout, this, &NivelBase::actualizarFrameParallax);
    temporizadorParallax->start(200);
}

void NivelBase::desplazarFondoParallax(float xJugador)
{
    if (copiasParallax.isEmpty()) return;

    float anchoImagen = copiasParallax.first()->pixmap().width();
    float xFondo      = -(xJugador * 0.3f);

    for (int i = 0; i < copiasParallax.size(); i++)
        copiasParallax[i]->setX(xFondo + anchoImagen * i);
}

void NivelBase::actualizarFrameParallax()
{
    if (copiasParallax.isEmpty()) return;

    frameParallaxActual = (frameParallaxActual + 1) % 4;

    QPixmap imagen = hojaParallax.copy(7 + (frameParallaxActual * 513), 18, 511, 431);
    if (imagen.isNull()) return;

    QRectF rect    = escena->sceneRect();
    float  escala  = rect.height() / imagen.height();
    int nuevoAncho = imagen.width() * escala;
    imagen = imagen.scaled(nuevoAncho, rect.height(), Qt::IgnoreAspectRatio);

    for (QGraphicsPixmapItem *copia : copiasParallax)
        if (copia && copia->scene())
            copia->setPixmap(imagen);
}

// ─── Fondo carretera vertical (nivel 2) ──────────────────────

void NivelBase::cargarFondoCarretera(const QString &rutaImagen)
{
    QPixmap mitadIzq(rutaImagen);
    QPixmap mitadDer = mitadIzq.transformed(QTransform().scale(-1, 1));

    QRectF rect      = escena->sceneRect();
    float anchoMitad = rect.width() / 2.0f;
    float altoVista  = rect.height();

    mitadIzq = mitadIzq.scaled(anchoMitad, altoVista, Qt::IgnoreAspectRatio);
    mitadDer = mitadDer.scaled(anchoMitad, altoVista, Qt::IgnoreAspectRatio);

    fondoCarretera1 = new QGraphicsPixmapItem(mitadIzq);
    fondoCarretera2 = new QGraphicsPixmapItem(mitadDer);
    fondoCarretera1->setPos(0,          0);
    fondoCarretera2->setPos(anchoMitad, 0);
    fondoCarretera1->setZValue(-1);
    fondoCarretera2->setZValue(-1);
    escena->addItem(fondoCarretera1);
    escena->addItem(fondoCarretera2);

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

    fondoCarretera1->setY(fondoCarretera1->y() + velocidad);
    fondoCarretera2->setY(fondoCarretera2->y() + velocidad);
    fondoCarretera3->setY(fondoCarretera3->y() + velocidad);
    fondoCarretera4->setY(fondoCarretera4->y() + velocidad);

    if (fondoCarretera1->y() >= altoVista) {
        fondoCarretera1->setY(fondoCarretera3->y() - altoVista);
        fondoCarretera2->setY(fondoCarretera4->y() - altoVista);
    }

    if (fondoCarretera3->y() >= altoVista) {
        fondoCarretera3->setY(fondoCarretera1->y() - altoVista);
        fondoCarretera4->setY(fondoCarretera2->y() - altoVista);
    }
}

// ─── Métodos comunes ──────────────────────────────────────────

void NivelBase::verificarEstado()
{
    if (nivelCompletado)
        emit nivelTerminado();
}

bool NivelBase::obtenerNivelCompletado() const { return nivelCompletado; }
