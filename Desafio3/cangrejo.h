#ifndef CANGREJO_H
#define CANGREJO_H

#include "enemigo.h"

class Cangrejo : public Enemigo
{
    Q_OBJECT

public:
    explicit Cangrejo(float x, float y, float limiteIzq, float limiteDer,
                      QObject *parent = nullptr);

    void actualizar() override;

protected:
    void cargarFrame(int indice) override;
};

#endif // CANGREJO_H
