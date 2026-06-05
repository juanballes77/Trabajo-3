#include "tiburon.h"

Tiburon::Tiburon(float x, float y, float limiteIzq, float limiteDer, QObject *parent)
    : Enemigo(x, y, limiteIzq, limiteDer, 2.8f, parent)
{
    hoja = QPixmap(":/tiburon.png");

    // Coordenadas de cada frame
    frames.append(QRect(553,  523, 217, 112)); // Frame 0
    frames.append(QRect(782,  523, 217, 112)); // Frame 1
    frames.append(QRect(1017, 521, 217, 112)); // Frame 2
    frames.append(QRect(1282, 518, 192, 112)); // Frame 3
    frames.append(QRect(1500, 523, 209, 112)); // Frame 4

    cargarFrame(0);
    setPos(x, y);
    setZValue(1);
}

void Tiburon::actualizar()
{
    patrullar();
}

void Tiburon::cargarFrame(int indice)
{
    if (hoja.isNull() || indice >= frames.size())
        return;

    QPixmap frame = hoja.copy(frames[indice]);

    if (!mirandoDerecha)
        frame = frame.transformed(QTransform().scale(-1, 1));

    setPixmap(frame);
}
