#ifndef ENEMIGOCICLISTA_H
#define ENEMIGOCICLISTA_H

#include "enemigo.h"

class EnemigoCiclista : public Enemigo
{
    Q_OBJECT

public:
    explicit EnemigoCiclista(float x, float y, float ancho, float alto,
                             QObject *parent = nullptr);

    void actualizar() override;
    void actualizar(float velocidadScroll, float limiteIzq, float limiteDer);

    float obtenerX() const;
    float obtenerY() const;

protected:
    void cargarFrame(int indice) override;

private:
    float   ancho;
    float   alto;
    float   velocidadExtra;
    float   velocidadLateral;
    int     frameAnimacion;
    int contadorFrame;
    QPixmap hojaCiclista;

    void cargarFrameCiclista(int indice);
};

#endif // ENEMIGOCICLISTA_H
