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
    frameAlternoRect(QRect()),
    usarSpriteAlternado(false),
    frameActual(0),
    moviendose(false),
    mirandoDerecha(true),
    limiteYMinimo(0.0f),
    limiteYMaximo(0.0f)
{
    // Coordenadas frames nivel 1
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

void Jugador::establecerSpriteNivel2(const QString &ruta, QRect frameRect)
{
    hojaAlterna         = QPixmap(ruta);
    frameAlternoRect    = frameRect;
    usarSpriteAlternado = true;
    frameActual         = 0;
    cargarFrame(0);
}

// ─── Física ───────────────────────────────────────────────────

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

    bool seEstaMoivendo = (velocidadX != 0.0f); // ← guardar antes de modificar

    x += velocidadX;

    if (x < 0) {
        x = 0;
        velocidadX = 0.0f;
    }

    if (gravedadActiva)
        y += velocidadY;

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

    if (!seEstaMoivendo) {
        moviendose = false;
        if (!usarSpriteAlternado)
            cargarFrame(0);
    }

    velocidadX = 0.0f;
}

// ─── Animación ────────────────────────────────────────────────

void Jugador::siguienteFrame()
{
    if (usarSpriteAlternado) {
        // Nivel 2: siempre anima independiente de teclas
        frameActual = (frameActual + 1) % 2;
        cargarFrame(frameActual);
    } else if (moviendose) {
        // Nivel 1: solo anima al moverse
        frameActual = (frameActual + 1) % frames.size();
        cargarFrame(frameActual);
    }
}

void Jugador::cargarFrame(int indice)
{
    if (usarSpriteAlternado && !hojaAlterna.isNull()) {
        QPixmap frame = hojaAlterna.copy(frameAlternoRect);

        // Alternar reflejo horizontal para simular pedaleo
        if (indice % 2 == 1)
            frame = frame.transformed(QTransform().scale(-1, 1));

        // Escalar al mismo tamaño que los rivales (50x80)
        frame = frame.scaled(50, 80, Qt::IgnoreAspectRatio);
        setPixmap(frame);
        return;
    }

    // Animación original nivel 1
    if (hoja.isNull() || indice >= frames.size()) return;
    QPixmap frame = hoja.copy(frames[indice]);
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
    gravedadActiva     = activa;
    usarSpriteAlternado = false; // resetear al cambiar de nivel
    if (!activa)
        velocidadY = 0.0f;
}

void Jugador::establecerLimites(float yMinimo, float yMaximo)
{
    limiteYMinimo = yMinimo;
    limiteYMaximo = yMaximo;
}
