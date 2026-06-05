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

    // Teclas
    bool teclaIzquierda;
    bool teclaDerecha;
    bool teclaAcelerar;

    // Scroll
    float velocidadScroll;

    // Límites de la carretera
    float carreteraIzquierda;
    float carreteraDerecha;

    float velocidadActual;      // Velocidad actual del scroll
    float velocidadMaxima;      // Velocidad máxima al acelerar
    float aceleracion;          // Cuánto aumenta por frame
    float desaceleracion;       // Cuánto disminuye por frame

    int repeticionesFondo;
    int repeticionesParaMeta;
    bool metaVisible;
    QGraphicsRectItem *metaNivel2;

    // Elementos del nivel
    QVector<Obstaculo*>      obstaculos;
    QVector<EnemigoCiclista*> enemigos;

    static const int INTERVALO_JUEGO_MS       = 16;
    static const int INTERVALO_OBSTACULOS_MS  = 3000; // Cada 3 segundos
    static const int INTERVALO_ENEMIGOS_MS    = 5000; // Cada 5 segundos

    void cargarCarretera();
    void cargarJugador();
    void cargarEnemigos();

    void procesarMovimiento();
    void liminarJugadorEnCarretera();
    void actualizarEnemigos();
    void actualizarObstaculos();
    void limpiarElementosFueraDePantalla();
    void verificarColisiones();
    void verificarMeta();
    void mostrarMeta();
    void establecerSpriteNivel2(const QString &ruta, QRect frameRect);
};

#endif // NIVEL2_H
