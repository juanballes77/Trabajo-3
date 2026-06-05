#ifndef TIBURON_H
#define TIBURON_H

#include "enemigo.h"

class Tiburon : public Enemigo
{
    Q_OBJECT

public:
    explicit Tiburon(float x, float y, float limiteIzq, float limiteDer,
                     QObject *parent = nullptr);

    void actualizar() override;

protected:
    void cargarFrame(int indice) override;
};

#endif // TIBURON_H
