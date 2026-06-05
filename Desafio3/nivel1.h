#ifndef NIVEL1_H
#define NIVEL1_H

#include <QTimer>
#include "nivelbase.h"

class Nivel1 : public NivelBase
{
    Q_OBJECT

public:
    explicit Nivel1(QGraphicsScene *escena, QObject *parent = nullptr);
    ~Nivel1();

    // Implementación de métodos virtuales
    void iniciar()   override;
    void pausar()    override;
    void reanudar()  override;
    void terminar()  override;

private slots:
    void actualizar();

private:
    QTimer *temporizadorJuego;

    static const int INTERVALO_JUEGO_MS = 16; // ~60 fps

    // Métodos de carga
    void cargarJugador();
    void cargarEnemigos();
    void cargarPlataformas();

    // Detección
    void verificarColisiones();
    void verificarMeta();
};

#endif // NIVEL1_H
