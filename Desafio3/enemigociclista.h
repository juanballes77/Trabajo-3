#ifndef ENEMIGOCICLISTA_H
#define ENEMIGOCICLISTA_H

#include <QGraphicsRectItem>
#include <QObject>

class EnemigoCiclista : public QObject, public QGraphicsRectItem
{
    Q_OBJECT

public:
    explicit EnemigoCiclista(float x, float y, float ancho, float alto, QObject *parent = nullptr);

    void actualizar(float velocidadScroll, float limiteIzq, float limiteDer);

    float obtenerX() const;
    float obtenerY() const;

private:
    float x;
    float y;
    float velocidadLateral;
    float velocidadExtra;   // Velocidad adicional al scroll
};

#endif // ENEMIGOCICLISTA_H
