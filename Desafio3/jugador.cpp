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
    estaVivo(true),
    gravedadActiva(true),
    frameActual(0),
    moviendose(false),
    mirandoDerecha(true),
    limiteYMinimo(0.0f),
    limiteYMaximo(0.0f)
{
    // Coordenadas individuales de cada frame
    frames.append(QRect(6,   4,  167, 71)); // Frame 0
    frames.append(QRect(178, 9,  161, 63)); // Frame 1
    frames.append(QRect(30,  88, 143, 71)); // Frame 2
    frames.append(QRect(179, 81, 122, 78)); // Frame 3

    hoja = QPixmap(":/personaje1.png");

    temporizadorAnimacion = new QTimer(this);
    connect(temporizadorAnimacion, &QTimer::timeout, this, &Jugador::siguienteFrame);
    temporizadorAnimacion->start(INTERVALO_ANIMACION_MS);

    cargarFrame(0);
}

// ─── Movimiento ───────────────────────────────────────────────

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

// ─── Física ───────────────────────────────────────────────────

void Jugador::aplicarGravedad()
{
    if (!gravedadActiva)
        return;

    velocidadY += gravedad;
    if (velocidadY > velocidadMaxCaida)
        velocidadY = velocidadMaxCaida;
}

void Jugador::actualizar()
{
    aplicarGravedad();

    x += velocidadX;

    // Límite izquierdo: no puede salir por la izquierda
    if (x < 0) {
        x = 0;
        velocidadX = 0.0f;
    }

    if (gravedadActiva)
        y += velocidadY;

    // Aplicar límites verticales
    if (limiteYMaximo > 0) {
        if (y < limiteYMinimo) {
            y = limiteYMinimo;
            velocidadY = 0.0f;
        }
        if (y + pixmap().height() > limiteYMaximo) {
            y = limiteYMaximo - pixmap().height();
            velocidadY = 0.0f;
        }
    }

    setPos(x, y);

    if (velocidadX == 0.0f) {
        moviendose = false;
        cargarFrame(0);
    }

    velocidadX = 0.0f;
}

// ─── Animación ────────────────────────────────────────────────

void Jugador::siguienteFrame()
{
    if (moviendose) {
        frameActual = (frameActual + 1) % frames.size();
        cargarFrame(frameActual);
    }
}

void Jugador::cargarFrame(int indice)
{
    if (hoja.isNull() || indice >= frames.size())
        return;

    QRect   rect  = frames[indice];
    QPixmap frame = hoja.copy(rect);

    if (mirandoDerecha)
        frame = frame.transformed(QTransform().scale(-1, 1));

    setPixmap(frame);
}

// ─── Getters ──────────────────────────────────────────────────

float Jugador::obtenerX() const { return x; }
float Jugador::obtenerY() const { return y; }
bool  Jugador::obtenerEstaVivo() const { return estaVivo; }

// ─── Setters ──────────────────────────────────────────────────

void Jugador::establecerPosicion(float x, float y)
{
    this->x = x;
    this->y = y;
    setPos(this->x, this->y);
}

void Jugador::establecerEstaVivo(bool estado)
{
    estaVivo = estado;
}

void Jugador::establecerGravedad(bool activa)
{
    gravedadActiva = activa;
    if (!activa)
        velocidadY = 0.0f;
}

void Jugador::establecerLimites(float yMinimo, float yMaximo)
{
    limiteYMinimo = yMinimo;
    limiteYMaximo = yMaximo;
}
