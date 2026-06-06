#ifndef NIVEL2_H
#define NIVEL2_H

#include <QTimer>
#include <QKeyEvent>
#include <QVector>
#include <QGraphicsRectItem>
#include "nivelbase.h"
#include "obstaculo.h"
#include "enemigociclista.h"

class Nivel2 : public NivelBase
{
    Q_OBJECT

public:
    explicit Nivel2(QGraphicsScene *escena, QObject *parent = nullptr);
    ~Nivel2();

    void iniciar()   override;
    void pausar()    override;
    void reanudar()  override;
    void terminar()  override;

    void teclaPresionada(QKeyEvent *evento);
    void teclaLiberada(QKeyEvent *evento);

private slots:
    void actualizar();
    void generarObstaculo();
    void generarEnemigo();

private:
    QTimer *temporizadorJuego;
    QTimer *temporizadorObstaculos;
    QTimer *temporizadorEnemigos;

    bool teclaIzquierda;
    bool teclaDerecha;
    bool teclaAcelerar;

    float velocidadScroll;
    float velocidadActual;
    float velocidadMaxima;
    float aceleracion;
    float desaceleracion;
    float carreteraIzquierda;
    float carreteraDerecha;

    int  repeticionesFondo;
    int  repeticionesParaMeta;
    bool metaVisible;
    QGraphicsRectItem *metaNivel2;

    QVector<Obstaculo*>       obstaculos;
    QVector<EnemigoCiclista*> enemigos;

    static const int INTERVALO_JUEGO_MS      = 16;
    static const int INTERVALO_OBSTACULOS_MS = 3000;
    static const int INTERVALO_ENEMIGOS_MS   = 5000;

    void cargarCarretera();
    void cargarJugador();

    void procesarMovimiento();
    void liminarJugadorEnCarretera();
    void actualizarEnemigos();
    void actualizarObstaculos();
    void limpiarElementosFueraDePantalla();
    void verificarColisiones();
    void verificarMeta();
    void mostrarMeta();
};

#endif // NIVEL2_H
