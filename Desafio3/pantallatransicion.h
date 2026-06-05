#ifndef PANTALLATRANSICION_H
#define PANTALLATRANSICION_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

class PantallaTransicion : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaTransicion(QWidget *parent = nullptr);

    void establecerTexto(const QString &titulo, const QString &descripcion);

signals:
    void continuar();

private:
    QLabel      *etiquetaTitulo;
    QLabel      *etiquetaDescripcion;
    QPushButton *botonContinuar;

    void configurarUI();
    void aplicarEstilos();
};

#endif // PANTALLATRANSICION_H
