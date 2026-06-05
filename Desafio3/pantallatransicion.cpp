#include "pantallatransicion.h"

PantallaTransicion::PantallaTransicion(QWidget *parent)
    : QWidget(parent)
{
    configurarUI();
    aplicarEstilos();
}

// ─── Construcción de la interfaz ──────────────────────────────

void PantallaTransicion::configurarUI()
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter);
    layout->setSpacing(30);

    // Título
    etiquetaTitulo = new QLabel("¡ETAPA COMPLETADA!", this);
    etiquetaTitulo->setAlignment(Qt::AlignCenter);
    etiquetaTitulo->setObjectName("etiquetaTitulo");

    // Descripción
    etiquetaDescripcion = new QLabel(this);
    etiquetaDescripcion->setAlignment(Qt::AlignCenter);
    etiquetaDescripcion->setWordWrap(true);
    etiquetaDescripcion->setObjectName("etiquetaDescripcion");

    // Botón continuar
    botonContinuar = new QPushButton("CONTINUAR", this);
    botonContinuar->setObjectName("botonContinuar");
    botonContinuar->setFixedSize(200, 60);
    botonContinuar->setCursor(Qt::PointingHandCursor);

    connect(botonContinuar, &QPushButton::clicked, this, &PantallaTransicion::continuar);

    layout->addWidget(etiquetaTitulo);
    layout->addWidget(etiquetaDescripcion);
    layout->addWidget(botonContinuar, 0, Qt::AlignCenter);

    setLayout(layout);
}

void PantallaTransicion::aplicarEstilos()
{
    setStyleSheet(R"(
        PantallaTransicion {
            background-color: #0a2a0a;
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

        QPushButton#botonContinuar {
            background-color: transparent;
            color: #ffd700;
            font-size: 20px;
            font-weight: bold;
            font-family: "Arial Black", sans-serif;
            letter-spacing: 4px;
            border: 2px solid #ffd700;
            border-radius: 4px;
        }

        QPushButton#botonContinuar:hover {
            background-color: #ffd700;
            color: #0a2a0a;
        }

        QPushButton#botonContinuar:pressed {
            background-color: #ccaa00;
            border-color: #ccaa00;
            color: #0a2a0a;
        }
    )");
}

// ─── Setter de texto ──────────────────────────────────────────

void PantallaTransicion::establecerTexto(const QString &titulo, const QString &descripcion)
{
    etiquetaTitulo->setText(titulo);
    etiquetaDescripcion->setText(descripcion);
}
