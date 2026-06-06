#ifndef CALAMAR_H
#define CALAMAR_H

#include "enemigo.h"

class Calamar : public Enemigo
{
    Q_OBJECT

public:
    explicit Calamar(float x, float y, QObject *parent = nullptr);

    void actualizar() override;
    void establecerObjetivo(float xJugador, float yJugador);

protected:
    void cargarFrame(int indice) override;

private:
    float xObjetivo;
    float yObjetivo;
    float factorLerpX;
    float factorLerpY;
};

#endif // CALAMAR_H
