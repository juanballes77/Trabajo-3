#ifndef NIVELBASE_H
#define NIVELBASE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include "jugador.h"
#include "fondo.h"

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

    void actualizarHUD();
    void verificarEstado();

    int  obtenerPuntaje()         const;
    int  obtenerVidasRestantes()  const;
    bool obtenerNivelCompletado() const;

protected:
    QGraphicsScene      *escena;
    Jugador             *jugador;
    Fondo               *fondo;           // Fondo animado (nivel 1)
    QGraphicsPixmapItem *fondoCarretera1; // Mitad izquierda
    QGraphicsPixmapItem *fondoCarretera2; // Mitad derecha (reflejada)
    QGraphicsPixmapItem *fondoCarretera3; // Copia B izquierda
    QGraphicsPixmapItem *fondoCarretera4; // Copia B derecha

    int  puntaje;
    int  vidasRestantes;
    bool nivelCompletado;
    bool estaPausado;

    void agregarPuntaje(int cantidad);
    void perderVida();

    void cargarFondo(const QString &rutaImagen);
    void cargarFondoCarretera(const QString &rutaImagen);
    void desplazarFondoCarretera(float velocidad);

signals:
    void nivelTerminado();
    void juegoTerminado();
};

#endif // NIVELBASE_H
