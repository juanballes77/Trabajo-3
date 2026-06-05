#ifndef NIVELBASE_H
#define NIVELBASE_H

#include <QObject>
#include <QGraphicsScene>
#include "jugador.h"
#include "fondo.h"

class NivelBase : public QObject
{
    Q_OBJECT

public:
    explicit NivelBase(QGraphicsScene *escena, QObject *parent = nullptr);
    virtual ~NivelBase();

    // Métodos virtuales puros (cada nivel los implementa)
    virtual void iniciar()   = 0;
    virtual void pausar()    = 0;
    virtual void reanudar()  = 0;
    virtual void terminar()  = 0;

    // Métodos comunes
    void actualizarHUD();
    void verificarEstado();

    // Getters
    int  obtenerPuntaje()         const;
    int  obtenerVidasRestantes()  const;
    bool obtenerNivelCompletado() const;

protected:
    QGraphicsScene *escena;
    Jugador        *jugador;
    Fondo          *fondo;      // Compartido entre niveles

    int  puntaje;
    int  vidasRestantes;
    bool nivelCompletado;
    bool estaPausado;

    // Métodos de apoyo para clases hijas
    void agregarPuntaje(int cantidad);
    void perderVida();

    // Carga del fondo (cada nivel pasa su propia imagen)
    void cargarFondo(const QString &rutaImagen);

signals:
    void nivelTerminado();
    void juegoTerminado();
};

#endif // NIVELBASE_H
