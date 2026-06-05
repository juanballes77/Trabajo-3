#include "cangrejo.h"

Cangrejo::Cangrejo(float x, float y, float limiteIzq, float limiteDer, QObject *parent)
    : Enemigo(x, y, limiteIzq, limiteDer, 2.0f, parent)
{
    hoja = QPixmap(":/cangrejo.png");

    // Coordenadas de cada frame
    frames.append(QRect(573,  842, 155, 84)); // Frame 0
    frames.append(QRect(798,  844, 160, 83)); // Frame 1
    frames.append(QRect(1027, 844, 162, 83)); // Frame 2
    frames.append(QRect(1262, 844, 152, 84)); // Frame 3
    frames.append(QRect(1501, 842, 156, 86)); // Frame 4

    cargarFrame(0);
    setPos(x, y);
    setZValue(1);
}

void Cangrejo::actualizar()
{
    patrullar();
}

void Cangrejo::cargarFrame(int indice)
{
    if (hoja.isNull() || indice >= frames.size())
        return;

    QPixmap frame = hoja.copy(frames[indice]);

    if (!mirandoDerecha)
        frame = frame.transformed(QTransform().scale(-1, 1));

    setPixmap(frame);
}
