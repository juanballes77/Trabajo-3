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

    void moverIzquierda();
    void moverDerecha();
    void impulsarse();
    void aplicarGravedad();
    void actualizar();

    float obtenerX() const;
    float obtenerY() const;

    void establecerPosicion(float x, float y);
    void establecerLimites(float yMaximo);
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
    float limiteYMaximo;
    bool  gravedadActiva;
    bool  usarSpriteAlternado;

    QPixmap        hoja;
    QPixmap        hojaAlterna;
    QRect          frameAlternoRect;
    QVector<QRect> frames;
    QTimer        *temporizadorAnimacion;
    int            frameActual;
    bool           moviendose;
    bool           mirandoDerecha;

    static const int INTERVALO_ANIMACION_MS = 150;

    void cargarFrame(int indice);
};

#endif // JUGADOR_H
