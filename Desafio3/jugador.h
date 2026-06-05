#ifndef JUGADOR_H
#define JUGADOR_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include <QPixmap>
#include <QRect>
#include <QVector>

class Jugador : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    explicit Jugador(QObject *parent = nullptr);

    // Movimiento
    void moverIzquierda();
    void moverDerecha();
    void impulsarse();

    // Física
    void aplicarGravedad();
    void actualizar();

    // Getters
    float obtenerX() const;
    float obtenerY() const;
    bool  obtenerEstaVivo() const;

    // Setters
    void establecerPosicion(float x, float y);
    void establecerEstaVivo(bool estado);
    void establecerLimites(float yMinimo, float yMaximo);
    void establecerGravedad(bool activa);
    void establecerVelocidad(float v);
    void establecerSpriteNivel2(const QString &ruta, QRect frameRect);

private slots:
    void siguienteFrame();

private:
    float x;
    float y;
    float velocidadX;
    float velocidadY;
    float velocidad;
    float fuerzaImpulso;
    float gravedad;
    float velocidadMaxCaida;
    float limiteYMinimo;
    float limiteYMaximo;
    bool  estaVivo;
    bool  gravedadActiva;

    // Animación nivel 1
    QPixmap        hoja;
    QVector<QRect> frames;

    // Animación nivel 2
    QPixmap hojaAlterna;
    QRect   frameAlternoRect;
    bool    usarSpriteAlternado;

    QTimer *temporizadorAnimacion;
    int     frameActual;
    bool    moviendose;
    bool    mirandoDerecha;

    static const int INTERVALO_ANIMACION_MS = 150;

    void cargarFrame(int indice);
};

#endif // JUGADOR_H
