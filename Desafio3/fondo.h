#ifndef FONDO_H
#define FONDO_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include <QPixmap>

class Fondo : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    explicit Fondo(const QString &rutaImagen, QObject *parent = nullptr);
    ~Fondo();

    void iniciar();
    void detener();

private slots:
    void siguienteFrame();

private:
    // Spritesheet completo
    QPixmap hoja;

    // Animación
    QTimer *temporizador;
    int     frameActual;
    int     totalFrames;

    // Dimensiones de cada frame en el spritesheet
    static const int FRAME_X      = 7;
    static const int FRAME_ANCHO  = 511;
    static const int FRAME_ALTO   = 431;

    // Y inicial de cada frame (alto + 1px separación)
    static const int FRAME_Y_BASE = 18;
    static const int FRAME_PASO   = 432; // 431 alto + 1 separación

    // Velocidad de animación (ms por frame)
    static const int INTERVALO_MS = 200;

    void cargarFrame(int indice);
};

#endif // FONDO_H
