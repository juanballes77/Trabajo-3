#ifndef NIVELBASE_H
#define NIVELBASE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QVector>
#include "jugador.h"

class NivelBase : public QObject
{
    Q_OBJECT

public:
    explicit NivelBase(QGraphicsScene *escena, QObject *parent = nullptr);
    virtual ~NivelBase();

    virtual void iniciar()   = 0;
    virtual void pausar()    = 0;
    virtual void reanudar()  = 0;
    virtual void terminar()  = 0;

    void verificarEstado();
    bool obtenerNivelCompletado() const;

protected:
    QGraphicsScene *escena;
    Jugador        *jugador;

    // Fondo parallax (nivel 1)
    QVector<QGraphicsPixmapItem*> copiasParallax;
    QTimer  *temporizadorParallax;
    int      frameParallaxActual;
    QPixmap  hojaParallax;

    // Fondo carretera (nivel 2)
    QGraphicsPixmapItem *fondoCarretera1;
    QGraphicsPixmapItem *fondoCarretera2;
    QGraphicsPixmapItem *fondoCarretera3;
    QGraphicsPixmapItem *fondoCarretera4;

    bool nivelCompletado;
    bool estaPausado;

    void cargarFondoParallax(const QString &rutaImagen);
    void desplazarFondoParallax(float xJugador);
    void cargarFondoCarretera(const QString &rutaImagen);
    void desplazarFondoCarretera(float velocidad);

private slots:
    void actualizarFrameParallax();

signals:
    void nivelTerminado();
    void juegoTerminado();
};

#endif // NIVELBASE_H
