#ifndef OBSTACULO_H
#define OBSTACULO_H

#include <QGraphicsRectItem>
#include <QObject>

class Obstaculo : public QObject, public QGraphicsRectItem
{
    Q_OBJECT

public:
    explicit Obstaculo(float x, float y, float ancho, float alto, QObject *parent = nullptr);

    float obtenerX()     const;
    float obtenerY()     const;
    float obtenerAncho() const;
    float obtenerAlto()  const;

private:
    float x;
    float y;
    float ancho;
    float alto;
};

#endif // OBSTACULO_H
