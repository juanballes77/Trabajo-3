#include "jugador.h"

Jugador::Jugador(QObject *parent)
    : QObject(parent),
    QGraphicsPixmapItem(),
    x(0.0f),
    y(0.0f),
    velocidadX(0.0f),
    velocidadY(0.0f),
    velocidad(4.0f),
    fuerzaImpulso(-8.0f),
    gravedad(0.2f),
    velocidadMaxCaida(3.0f),
    limiteYMaximo(0.0f),
    gravedadActiva(true),
    usarSpriteAlternado(false),
    frameAlternoRect(QRect()),
    frameActual(0),
    moviendose(false),
    mirandoDerecha(true)
{
    frames.append(QRect(6,   4,  167, 71));
    frames.append(QRect(178, 9,  161, 63));
    frames.append(QRect(30,  88, 143, 71));
    frames.append(QRect(179, 81, 122, 78));

    hoja = QPixmap(":/personaje1.png");

    temporizadorAnimacion = new QTimer(this);
    connect(temporizadorAnimacion, &QTimer::timeout, this, &Jugador::siguienteFrame);
    temporizadorAnimacion->start(INTERVALO_ANIMACION_MS);

    cargarFrame(0);
}

void Jugador::moverIzquierda()
{
    velocidadX     = -velocidad;
    moviendose     = true;
    mirandoDerecha = false;
}

void Jugador::moverDerecha()
{
    velocidadX     = velocidad;
    moviendose     = true;
    mirandoDerecha = true;
}

void Jugador::impulsarse()
{
    if (gravedadActiva)
        velocidadY = fuerzaImpulso;
}

void Jugador::establecerVelocidad(float v)
{
    velocidad = v;
}

void Jugador::establecerSpriteNivel2(const QString &ruta, QRect frameRect)
{
    hojaAlterna         = QPixmap(ruta);
    frameAlternoRect    = frameRect;
    usarSpriteAlternado = true;
    frameActual         = 0;
    cargarFrame(0);
}

void Jugador::aplicarGravedad()
{
    if (!gravedadActiva) return;

    velocidadY += gravedad;
    if (velocidadY > velocidadMaxCaida)
        velocidadY = velocidadMaxCaida;
}

void Jugador::actualizar()
{
    aplicarGravedad();

    bool seEstaMoviendo = (velocidadX != 0.0f);

    x += velocidadX;
    if (x < 0) {
        x = 0;
        velocidadX = 0.0f;
    }

    if (gravedadActiva)
        y += velocidadY;

    if (limiteYMaximo > 0) {
        if (y < 0) {
            y = 0;
            velocidadY = 0.0f;
        }
        if (y + pixmap().height() > limiteYMaximo) {
            y = limiteYMaximo - pixmap().height();
            velocidadY = 0.0f;
        }
    }

    setPos(x, y);

    if (!seEstaMoviendo) {
        moviendose = false;
        if (!usarSpriteAlternado)
            cargarFrame(0);
    }

    velocidadX = 0.0f;
}

void Jugador::siguienteFrame()
{
    if (usarSpriteAlternado) {
        frameActual = (frameActual + 1) % 2;
        cargarFrame(frameActual);
    } else if (moviendose) {
        frameActual = (frameActual + 1) % frames.size();
        cargarFrame(frameActual);
    }
}

void Jugador::cargarFrame(int indice)
{
    if (usarSpriteAlternado && !hojaAlterna.isNull()) {
        QPixmap frame = hojaAlterna.copy(frameAlternoRect);
        if (indice % 2 == 1)
            frame = frame.transformed(QTransform().scale(-1, 1));
        frame = frame.scaled(50, 80, Qt::IgnoreAspectRatio);
        setPixmap(frame);
        return;
    }

    if (hoja.isNull() || indice >= frames.size()) return;
    QPixmap frame = hoja.copy(frames[indice]);
    if (mirandoDerecha)
        frame = frame.transformed(QTransform().scale(-1, 1));
    setPixmap(frame);
}

float Jugador::obtenerX() const { return x; }
float Jugador::obtenerY() const { return y; }

void Jugador::establecerPosicion(float x, float y)
{
    this->x = x;
    this->y = y;
    setPos(this->x, this->y);
}

void Jugador::establecerGravedad(bool activa)
{
    gravedadActiva      = activa;
    usarSpriteAlternado = false;
    if (!activa)
        velocidadY = 0.0f;
}

void Jugador::establecerLimites(float yMaximo)
{
    limiteYMaximo = yMaximo;
}
