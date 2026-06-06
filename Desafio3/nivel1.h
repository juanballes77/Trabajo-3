#ifndef NIVEL1_H
#define NIVEL1_H

#include <QTimer>
#include <QKeyEvent>
#include <QVector>
#include <QTransform>
#include "nivelbase.h"
#include "obstaculo.h"
#include "meta.h"
#include "tiburon.h"
#include "cangrejo.h"
#include "calamar.h"

class Nivel1 : public NivelBase
{
    Q_OBJECT

public:
    explicit Nivel1(QGraphicsScene *escena, QObject *parent = nullptr);
    ~Nivel1();

    void iniciar()   override;
    void pausar()    override;
    void reanudar()  override;
    void terminar()  override;

    void teclaPresionada(QKeyEvent *evento);
    void teclaLiberada(QKeyEvent *evento);

private slots:
    void actualizar();

private:
    QTimer *temporizadorJuego;

    bool teclaIzquierda;
    bool teclaDerecha;
    bool teclaImpulso;

    float velocidadJugador;
    static constexpr float VELOCIDAD_NORMAL   = 4.0f;
    static constexpr float VELOCIDAD_REDUCIDA = 0.8f;

    QVector<Obstaculo*> obstaculos;
    QVector<Tiburon*>   tiburones;
    QVector<Cangrejo*>  cangrejos;
    Calamar            *calamar;
    Meta               *metaNivel;
    float               altoEscena;

    static const int LONGITUD_NIVEL     = 10000;
    static const int INTERVALO_JUEGO_MS = 16;

    void cargarJugador();
    void cargarObstaculos();
    void cargarMeta();
    void cargarEnemigos();

    void procesarMovimiento();
    void actualizarEnemigos();
    void verificarColisiones();
    void verificarMeta();
};

#endif // NIVEL1_H
