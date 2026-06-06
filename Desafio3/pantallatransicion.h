#ifndef PANTALLATRANSICION_H
#define PANTALLATRANSICION_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPaintEvent>
#include <QPainter>

class PantallaTransicion : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaTransicion(QWidget *parent = nullptr);

    void establecerTexto(const QString &titulo, const QString &descripcion);
    void establecerModoFinal(bool esFinal);
    void establecerTiemposPodio(const QString &oro, const QString &plata, const QString &bronce);

signals:
    void continuar();

protected:
    void paintEvent(QPaintEvent *evento) override;

private:
    QLabel      *etiquetaTitulo;
    QLabel      *etiquetaDescripcion;
    QLabel      *etiquetaImagen;
    QWidget     *etiquetaPodio;
    QLabel      *etiquetaTiempoOro;
    QLabel      *etiquetaTiempoPlata;
    QLabel      *etiquetaTiempoBronce;
    QPushButton *botonContinuar;
    bool         esModoFinal;

    void configurarUI();
    void aplicarEstilos();
};

#endif // PANTALLATRANSICION_H
