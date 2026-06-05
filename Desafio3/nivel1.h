#ifndef NIVEL1_H
#define NIVEL1_H

#include <QTimer>
#include <QKeyEvent>
#include <QVector>
#include "nivelbase.h"
#include "obstaculo.h"
#include "meta.h"

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

    // Teclas
    bool teclaIzquierda;
    bool teclaDerecha;
    bool teclaImpulso;

    // Elementos del nivel
    QVector<Obstaculo*> obstaculos;
    Meta               *metaNivel;

    // Longitud del nivel
    static const int LONGITUD_NIVEL  = 5000;
    static const int INTERVALO_JUEGO_MS = 16;

    void cargarJugador();
    void cargarObstaculos();
    void cargarMeta();
    void cargarEnemigos();

    void procesarMovimiento();
    void verificarColisiones();
    void verificarMeta();
};

#endif // NIVEL1_H
