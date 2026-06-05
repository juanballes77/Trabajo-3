#include "calamar.h"

Calamar::Calamar(float x, float y, QObject *parent)
    : Enemigo(x, y, 0, 0, 0, parent),
    xObjetivo(x),
    yObjetivo(y),
    factorLerpX(0.021f),
    factorLerpY(0.019f),   // Movimiento suave con retraso
    fuerzaEmpuje(80.0f)  // Píxeles que empuja hacia atrás
{
    hoja = QPixmap(":/calamar.png");

    frames.append(QRect(565,  738, 127, 139)); // Frame 0
    frames.append(QRect(799,  737, 162, 139)); // Frame 1
    frames.append(QRect(1031, 758, 176, 101)); // Frame 2
    frames.append(QRect(1262, 780, 187, 65 )); // Frame 3
    frames.append(QRect(1495, 756, 155, 106)); // Frame 4

    cargarFrame(0);
    setPos(x, y);
    setZValue(1);
}

void Calamar::establecerObjetivo(float xJugador, float yJugador)
{
    xObjetivo = xJugador;
    yObjetivo = yJugador;
}

void Calamar::actualizar()
{
    // Persecución con lerp — se mueve suavemente hacia el jugador
    x += (xObjetivo - x) * factorLerpX;
    y += (yObjetivo - y) * factorLerpY;

    // Voltear según dirección
    mirandoDerecha = xObjetivo > x;

    setPos(x, y);
}

void Calamar::cargarFrame(int indice)
{
    if (hoja.isNull() || indice >= frames.size())
        return;

    QPixmap frame = hoja.copy(frames[indice]);

    if (!mirandoDerecha)
        frame = frame.transformed(QTransform().scale(-1, 1));

    setPixmap(frame);
}
