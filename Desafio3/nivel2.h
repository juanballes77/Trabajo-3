#ifndef NIVEL2_H
#define NIVEL2_H

#include <QTimer>
#include "nivelbase.h"

class Nivel2 : public NivelBase
{
    Q_OBJECT

public:
    explicit Nivel2(QGraphicsScene *escena, QObject *parent = nullptr);
    ~Nivel2();

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

    // Métodos de carga (cargarFondo() se hereda de NivelBase)
    void cargarJugador();
    void cargarEnemigos();
    void cargarPlataformas();

    // Detección
    void verificarColisiones();
    void verificarMeta();
};

#endif // NIVEL2_H
