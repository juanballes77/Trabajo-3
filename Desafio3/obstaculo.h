#ifndef OBSTACULO_H
#define OBSTACULO_H

#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QPixmap>
#include <QPainter>

class Obstaculo : public QObject, public QGraphicsRectItem
{
    Q_OBJECT

public:
    explicit Obstaculo(float x, float y, float ancho, float alto,
                       bool usarSprite = false, QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    float obtenerX()     const;
    float obtenerY()     const;
    float obtenerAncho() const;
    float obtenerAlto()  const;

private:
    float x;
    float y;
    float ancho;
    float alto;
    bool  usarSprite;
    QPixmap textura;
};

#endif // OBSTACULO_H
