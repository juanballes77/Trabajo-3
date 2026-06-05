#ifndef PANTALLAFINAL_H
#define PANTALLAFINAL_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

class PantallaFinal : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaFinal(QWidget *parent = nullptr);

signals:
    void reiniciar();

private:
    QLabel      *etiquetaTitulo;
    QLabel      *etiquetaDescripcion;
    QPushButton *botonReiniciar;

    void configurarUI();
    void aplicarEstilos();
};

#endif // PANTALLAFINAL_H
