#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

class Menu : public QWidget
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = nullptr);

signals:
    void jugarPresionado();

private:
    QLabel      *etiquetaTitulo;
    QPushButton *botonJugar;

    void configurarUI();
    void aplicarEstilos();
};

#endif // MENU_H
