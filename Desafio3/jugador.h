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

    // Movimiento nivel acuático
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
    bool  estaVivo;

    // Animación
    QPixmap        hoja;
    QTimer        *temporizadorAnimacion;
    int            frameActual;
    bool           moviendose;
    bool           mirandoDerecha;
    QVector<QRect> frames; // Coordenadas individuales de cada frame

    static const int INTERVALO_ANIMACION_MS = 150;

    void cargarFrame(int indice);
};

#endif // JUGADOR_H
