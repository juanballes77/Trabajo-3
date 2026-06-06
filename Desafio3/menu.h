#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QPaintEvent>
#include <QPainter>
#include <QDialog>

class Menu : public QWidget
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = nullptr);

signals:
    void jugarPresionado();

protected:
    void paintEvent(QPaintEvent *evento) override;

private slots:
    void mostrarInstrucciones();

private:
    QLabel      *etiquetaTitulo;
    QPushButton *botonJugar;
    QPushButton *botonInstrucciones;

    void configurarUI();
    void aplicarEstilos();
};

#endif // MENU_H
