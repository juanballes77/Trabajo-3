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
    QPixmap hoja;
    QTimer *temporizador;
    int     frameActual;
    int     totalFrames;

    static const int FRAME_X      = 7;
    static const int FRAME_Y      = 18;
    static const int FRAME_ANCHO  = 511;
    static const int FRAME_ALTO   = 431;
    static const int FRAME_PASO   = 513;
    static const int INTERVALO_MS = 200;

    void cargarFrame(int indice);
};

#endif // FONDO_H
