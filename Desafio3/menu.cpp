#include "menu.h"
#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>

Menu::Menu(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_StyledBackground, true);
    configurarUI();
    aplicarEstilos();
}

void Menu::paintEvent(QPaintEvent *evento)
{
    QPainter painter(this);
    QPixmap fondo(":/imageninicial.jpg");
    if (!fondo.isNull())
        painter.drawPixmap(rect(), fondo);
    QWidget::paintEvent(evento);
}

void Menu::configurarUI()
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter);
    layout->setSpacing(20);

    etiquetaTitulo = new QLabel("NOMBRE DEL JUEGO", this);
    etiquetaTitulo->setAlignment(Qt::AlignCenter);
    etiquetaTitulo->setObjectName("etiquetaTitulo");

    botonJugar = new QPushButton("JUGAR", this);
    botonJugar->setObjectName("botonJugar");
    botonJugar->setFixedSize(200, 60);
    botonJugar->setCursor(Qt::PointingHandCursor);

    botonInstrucciones = new QPushButton("INSTRUCCIONES", this);
    botonInstrucciones->setObjectName("botonInstrucciones");
    botonInstrucciones->setFixedSize(200, 60);
    botonInstrucciones->setCursor(Qt::PointingHandCursor);

    connect(botonJugar, &QPushButton::clicked, this, &Menu::jugarPresionado);
    connect(botonInstrucciones, &QPushButton::clicked, this, &Menu::mostrarInstrucciones);

    layout->addWidget(etiquetaTitulo);
    layout->addWidget(botonJugar,          0, Qt::AlignCenter);
    layout->addWidget(botonInstrucciones,  0, Qt::AlignCenter);

    setLayout(layout);
}

void Menu::mostrarInstrucciones()
{
    QDialog *dialogo = new QDialog(this);
    dialogo->setWindowTitle("Instrucciones");
    dialogo->setFixedSize(600, 400);
    dialogo->setStyleSheet("background-color: #0a1628;");

    QVBoxLayout *layout = new QVBoxLayout(dialogo);
    layout->setSpacing(20);
    layout->setContentsMargins(40, 40, 40, 40);

    QLabel *titulo = new QLabel("¿CÓMO JUGAR?", dialogo);
    titulo->setAlignment(Qt::AlignCenter);
    titulo->setStyleSheet("color: #00e5ff; font-size: 28px; font-weight: bold; font-family: 'Arial Black';");

    QLabel *texto = new QLabel(
        "Tu objetivo es completar un triatlón de dos etapas en el menor tiempo posible.\n\n"
        "🏊  ETAPA 1 — NATACIÓN\n"
        "Nada desde el inicio hasta la línea de meta esquivando obstáculos y criaturas marinas. "
        "Usa A y D para moverte y ESPACIO para impulsarte hacia arriba.\n\n"
        "🚴  ETAPA 2 — CICLISMO\n"
        "Pedalea por la carretera evitando rocas y ciclistas rivales. "
        "Usa A y D para cambiar de carril y ESPACIO para acelerar.\n\n"
        "¡El tiempo no se detiene! Llega a la meta lo más rápido que puedas.",
        dialogo
        );
    texto->setAlignment(Qt::AlignLeft);
    texto->setWordWrap(true);
    texto->setStyleSheet("color: #ffffff; font-size: 14px; font-family: 'Arial';");

    QPushButton *botonCerrar = new QPushButton("ENTENDIDO", dialogo);
    botonCerrar->setFixedSize(150, 45);
    botonCerrar->setCursor(Qt::PointingHandCursor);
    botonCerrar->setStyleSheet(
        "QPushButton { background-color: transparent; color: #00e5ff; font-size: 16px; "
        "font-weight: bold; border: 2px solid #00e5ff; border-radius: 4px; }"
        "QPushButton:hover { background-color: #00e5ff; color: #0a1628; }"
        );
    connect(botonCerrar, &QPushButton::clicked, dialogo, &QDialog::accept);

    layout->addWidget(titulo);
    layout->addWidget(texto);
    layout->addWidget(botonCerrar, 0, Qt::AlignCenter);

    dialogo->exec();
}

void Menu::aplicarEstilos()
{
    setStyleSheet(R"(
        QLabel#etiquetaTitulo {
            color: #00e5ff;
            font-size: 52px;
            font-weight: bold;
            font-family: "Arial Black", sans-serif;
            letter-spacing: 6px;
            background-color: rgba(0, 0, 0, 150);
            padding: 10px 20px;
            border-radius: 8px;
        }

        QPushButton#botonJugar {
            background-color: rgba(0, 0, 0, 150);
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

        QPushButton#botonInstrucciones {
            background-color: rgba(0, 0, 0, 150);
            color: #00e5ff;
            font-size: 20px;
            font-weight: bold;
            font-family: "Arial Black", sans-serif;
            letter-spacing: 4px;
            border: 2px solid #00e5ff;
            border-radius: 4px;
        }

        QPushButton#botonInstrucciones:hover {
            background-color: #00e5ff;
            color: #0a1628;
        }

        QPushButton#botonInstrucciones:pressed {
            background-color: #00b8cc;
            border-color: #00b8cc;
            color: #0a1628;
        }
    )");
}
