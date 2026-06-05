#include "obstaculo.h"
#include <QPen>
#include <cstdlib>

Obstaculo::Obstaculo(float x, float y, float ancho, float alto,
                     bool usarSprite, QObject *parent)
    : QObject(parent),
    QGraphicsRectItem(x, y, ancho, alto),
    x(x),
    y(y),
    ancho(ancho),
    alto(alto),
    usarSprite(usarSprite)
{
    setPen(Qt::NoPen);
    setBrush(Qt::NoBrush);
    setZValue(0);

    QPixmap hoja(":/roca.png");

    if (usarSprite) {
        // Textura de roca para nivel 2
        textura = hoja.copy(164, 198, 13, 13);
        textura = textura.scaled(30, 30, Qt::IgnoreAspectRatio);
    } else {
        // Textura de muro para nivel 1
        int indice   = std::rand() % 3;
        int yTextura = 93 + (indice * 8);
        textura = hoja.copy(77, yTextura, 15, 7);
        textura = textura.scaled(30, 14, Qt::IgnoreAspectRatio);
    }
}

void Obstaculo::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    if (textura.isNull()) return;

    int tw = textura.width();
    int th = textura.height();

    // Usar coordenadas del rect local
    QRectF r = rect();

    for (int iy = r.y(); iy < r.y() + r.height(); iy += th) {
        for (int ix = r.x(); ix < r.x() + r.width(); ix += tw) {
            painter->drawPixmap(ix, iy, textura);
        }
    }
}

float Obstaculo::obtenerX()     const { return x; }
float Obstaculo::obtenerY()     const { return y; }
float Obstaculo::obtenerAncho() const { return ancho; }
float Obstaculo::obtenerAlto()  const { return alto; }
