#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QPixmap>
#include <QVector>
#include <QRect>

class Enemigo : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    explicit Enemigo(float x, float y, float limiteIzq, float limiteDer,
                     float velocidad, QObject *parent = nullptr);
    virtual ~Enemigo();

    virtual void actualizar() = 0;

    float obtenerX() const;
    float obtenerY() const;
    bool  obtenerEstaVivo() const;
    void  establecerEstaVivo(bool estado);

protected:
    float x;
    float y;
    float velocidad;
    float limiteIzquierdo;
    float limiteDerecho;
    float direccion;    // 1 = derecha, -1 = izquierda
    bool  estaVivo;

    // Animación
    QPixmap        hoja;
    QTimer        *temporizadorAnimacion;
    int            frameActual;
    QVector<QRect> frames;
    bool           mirandoDerecha;

    void patrullar();
    void siguienteFrame();
    virtual void cargarFrame(int indice) = 0;

private slots:
    void onSiguienteFrame();
};

#endif // ENEMIGO_H
