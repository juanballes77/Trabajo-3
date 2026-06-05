#include "pantallafinal.h"

PantallaFinal::PantallaFinal(QWidget *parent)
    : QWidget(parent)
{
    configurarUI();
    aplicarEstilos();
}

void PantallaFinal::configurarUI()
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter);
    layout->setSpacing(30);

    etiquetaTitulo = new QLabel("¡TRIATLÓN COMPLETADO!", this);
    etiquetaTitulo->setAlignment(Qt::AlignCenter);
    etiquetaTitulo->setObjectName("etiquetaTitulo");

    etiquetaDescripcion = new QLabel(
        "¡Felicitaciones!\nHas completado las etapas de\nnatación y ciclismo.", this);
    etiquetaDescripcion->setAlignment(Qt::AlignCenter);
    etiquetaDescripcion->setWordWrap(true);
    etiquetaDescripcion->setObjectName("etiquetaDescripcion");

    botonReiniciar = new QPushButton("JUGAR DE NUEVO", this);
    botonReiniciar->setObjectName("botonReiniciar");
    botonReiniciar->setFixedSize(250, 60);
    botonReiniciar->setCursor(Qt::PointingHandCursor);

    connect(botonReiniciar, &QPushButton::clicked, this, &PantallaFinal::reiniciar);

    layout->addWidget(etiquetaTitulo);
    layout->addWidget(etiquetaDescripcion);
    layout->addWidget(botonReiniciar, 0, Qt::AlignCenter);

    setLayout(layout);
}

void PantallaFinal::aplicarEstilos()
{
    setStyleSheet(R"(
        PantallaFinal {
            background-color: #1a0a2a;
        }

        QLabel#etiquetaTitulo {
            color: #ffd700;
            font-size: 48px;
            font-weight: bold;
            font-family: "Arial Black", sans-serif;
            letter-spacing: 4px;
        }

        QLabel#etiquetaDescripcion {
            color: #ffffff;
            font-size: 22px;
            font-family: "Arial", sans-serif;
            padding: 0 60px;
        }

        QPushButton#botonReiniciar {
            background-color: transparent;
            color: #ffd700;
            font-size: 20px;
            font-weight: bold;
            font-family: "Arial Black", sans-serif;
            letter-spacing: 4px;
            border: 2px solid #ffd700;
            border-radius: 4px;
        }

        QPushButton#botonReiniciar:hover {
            background-color: #ffd700;
            color: #1a0a2a;
        }

        QPushButton#botonReiniciar:pressed {
            background-color: #ccaa00;
            border-color: #ccaa00;
            color: #1a0a2a;
        }
    )");
}
