#ifndef JUGADOR_H
#define JUGADOR_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Jugador : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    explicit Jugador(QObject *parent = nullptr);

    // Movimiento
    void moverIzquierda();
    void moverDerecha();
    void saltar();

    // Física
    void aplicarGravedad();
    void actualizar();

    // Getters
    float obtenerX() const;
    float obtenerY() const;
    bool obtenerEstaVivo() const;
    bool obtenerEstaEnSuelo() const;

    // Setters
    void establecerPosicion(float x, float y);
    void establecerEstaEnSuelo(bool estado);
    void establecerEstaVivo(bool estado);

private:
    float x;
    float y;
    float velocidadX;
    float velocidadY;
    float velocidad;
    float fuerzaSalto;
    float gravedad;
    bool  estaEnSuelo;
    bool  estaVivo;
};

#endif // JUGADOR_H
