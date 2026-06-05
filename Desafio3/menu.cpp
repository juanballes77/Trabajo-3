#include "menu.h"

Menu::Menu(QWidget *parent)
    : QWidget(parent)
{
    configurarUI();
    aplicarEstilos();
}

// ─── Construcción de la interfaz ──────────────────────────────

void Menu::configurarUI()
{
    // Layout principal centrado
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter);
    layout->setSpacing(40);

    // Título del juego
    etiquetaTitulo = new QLabel("NOMBRE DEL JUEGO", this);
    etiquetaTitulo->setAlignment(Qt::AlignCenter);
    etiquetaTitulo->setObjectName("etiquetaTitulo");

    // Botón jugar
    botonJugar = new QPushButton("JUGAR", this);
    botonJugar->setObjectName("botonJugar");
    botonJugar->setFixedSize(200, 60);
    botonJugar->setCursor(Qt::PointingHandCursor);

    // Conectar señal
    connect(botonJugar, &QPushButton::clicked, this, &Menu::jugarPresionado);

    // Agregar al layout
    layout->addWidget(etiquetaTitulo);
    layout->addWidget(botonJugar, 0, Qt::AlignCenter);

    setLayout(layout);
}

void Menu::aplicarEstilos()
{
    // Fondo oscuro del menú
    setStyleSheet(R"(
        Menu {
            background-color: #0a1628;
        }

        QLabel#etiquetaTitulo {
            color: #00e5ff;
            font-size: 52px;
            font-weight: bold;
            font-family: "Arial Black", sans-serif;
            letter-spacing: 6px;
        }

        QPushButton#botonJugar {
            background-color: transparent;
            color: #00e5ff;
            font-size: 20px;
            font-weight: bold;
            font-family: "Arial Black", sans-serif;
            letter-spacing: 4px;
            border: 2px solid #00e5ff;
            border-radius: 4px;
        }

        QPushButton#botonJugar:hover {
            background-color: #00e5ff;
            color: #0a1628;
        }

        QPushButton#botonJugar:pressed {
            background-color: #00b8cc;
            border-color: #00b8cc;
            color: #0a1628;
        }
    )");
}
