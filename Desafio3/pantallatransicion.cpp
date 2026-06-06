#include "pantallatransicion.h"
#include <QApplication>
#include <QPixmap>
#include <QScreen>
#include <QFrame>

PantallaTransicion::PantallaTransicion(QWidget *parent)
    : QWidget(parent),
    esModoFinal(false)
{
    setAttribute(Qt::WA_StyledBackground, true);
    configurarUI();
    aplicarEstilos();
}

void PantallaTransicion::paintEvent(QPaintEvent *evento)
{
    QPainter painter(this);
    QPixmap fondo;

    if (esModoFinal)
        fondo = QPixmap(":/fondofinal.jpg");
    else
        fondo = QPixmap(":/fondointermedio.png");

    if (!fondo.isNull())
        painter.drawPixmap(rect(), fondo);

    QWidget::paintEvent(evento);
}

void PantallaTransicion::configurarUI()
{
    QVBoxLayout *layoutPrincipal = new QVBoxLayout(this);
    layoutPrincipal->setAlignment(Qt::AlignCenter);
    layoutPrincipal->setSpacing(20);
    layoutPrincipal->setContentsMargins(0, 40, 0, 40);

    // ── Título ────────────────────────────────────────
    etiquetaTitulo = new QLabel("¡ETAPA COMPLETADA!", this);
    etiquetaTitulo->setAlignment(Qt::AlignCenter);
    etiquetaTitulo->setObjectName("etiquetaTitulo");

    // ── Descripción ───────────────────────────────────
    etiquetaDescripcion = new QLabel(this);
    etiquetaDescripcion->setAlignment(Qt::AlignCenter);
    etiquetaDescripcion->setWordWrap(true);
    etiquetaDescripcion->setObjectName("etiquetaDescripcion");

    // ── Imagen final ──────────────────────────────────
    etiquetaImagen = new QLabel(this);
    etiquetaImagen->setAlignment(Qt::AlignCenter);
    etiquetaImagen->setVisible(false);

    QPixmap imgFinal(":/imagenfinal.jpg");
    if (!imgFinal.isNull()) {
        QScreen *pantalla = QApplication::primaryScreen();
        QSize tamPantalla = pantalla->availableSize();
        imgFinal = imgFinal.scaled(tamPantalla * 0.5, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        etiquetaImagen->setPixmap(imgFinal);
    }

    // ── Podio ─────────────────────────────────────────
    QWidget *widgetPodio = new QWidget(this);
    widgetPodio->setObjectName("widgetPodio");
    widgetPodio->setVisible(false);
    widgetPodio->setStyleSheet("background: transparent;");

    QHBoxLayout *layoutPodio = new QHBoxLayout(widgetPodio);
    layoutPodio->setSpacing(60);
    layoutPodio->setContentsMargins(80, 0, 80, 0);

    // ── Medalla oro ───────────────────────────────────
    QPixmap hojaOro(":/medallas.png");
    QPixmap spriteOro = hojaOro.copy(14, 135, 326, 543);
    spriteOro = spriteOro.scaled(80, 133, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QLabel *medallaOro = new QLabel();
    medallaOro->setPixmap(spriteOro);
    medallaOro->setAlignment(Qt::AlignCenter);
    medallaOro->setStyleSheet("background: transparent;");

    QLabel *tituloOro = new QLabel("PRIMER LUGAR");
    QLabel *tiempoOro = new QLabel("Menos de 02:22:00");
    tituloOro->setAlignment(Qt::AlignCenter);
    tiempoOro->setAlignment(Qt::AlignCenter);
    tituloOro->setStyleSheet("color: #ffd700; font-size: 15px; font-weight: bold; font-family: 'Arial Black'; background: transparent;");
    tiempoOro->setStyleSheet("color: #ffffff; font-size: 13px; font-family: 'Arial'; background: transparent;");

    QFrame *frameOro = new QFrame(widgetPodio);
    frameOro->setStyleSheet("background-color: rgba(0,0,0,170); border-radius: 8px;");
    QVBoxLayout *layoutOro = new QVBoxLayout(frameOro);
    layoutOro->setSpacing(5);
    layoutOro->setContentsMargins(15, 10, 15, 10);
    layoutOro->addWidget(medallaOro);
    layoutOro->addWidget(tituloOro);
    layoutOro->addWidget(tiempoOro);

    // ── Medalla plata ─────────────────────────────────
    QPixmap hojaPlata(":/medallas.png");
    QPixmap spritePlata = hojaPlata.copy(350, 135, 326, 543);
    spritePlata = spritePlata.scaled(80, 133, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QLabel *medallaPlata = new QLabel();
    medallaPlata->setPixmap(spritePlata);
    medallaPlata->setAlignment(Qt::AlignCenter);
    medallaPlata->setStyleSheet("background: transparent;");

    QLabel *tituloPlata = new QLabel("SEGUNDO LUGAR");
    QLabel *tiempoPlata = new QLabel("Menos de 02:36:00");
    tituloPlata->setAlignment(Qt::AlignCenter);
    tiempoPlata->setAlignment(Qt::AlignCenter);
    tituloPlata->setStyleSheet("color: #c0c0c0; font-size: 15px; font-weight: bold; font-family: 'Arial Black'; background: transparent;");
    tiempoPlata->setStyleSheet("color: #ffffff; font-size: 13px; font-family: 'Arial'; background: transparent;");

    QFrame *framePlata = new QFrame(widgetPodio);
    framePlata->setStyleSheet("background-color: rgba(0,0,0,170); border-radius: 8px;");
    QVBoxLayout *layoutPlata = new QVBoxLayout(framePlata);
    layoutPlata->setSpacing(5);
    layoutPlata->setContentsMargins(15, 10, 15, 10);
    layoutPlata->addWidget(medallaPlata);
    layoutPlata->addWidget(tituloPlata);
    layoutPlata->addWidget(tiempoPlata);

    // ── Medalla bronce ────────────────────────────────
    QPixmap hojaBronce(":/medallas.png");
    QPixmap spriteBronce = hojaBronce.copy(686, 135, 326, 543);
    spriteBronce = spriteBronce.scaled(80, 133, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QLabel *medallaBronce = new QLabel();
    medallaBronce->setPixmap(spriteBronce);
    medallaBronce->setAlignment(Qt::AlignCenter);
    medallaBronce->setStyleSheet("background: transparent;");

    QLabel *tituloBronce = new QLabel("TERCER LUGAR");
    QLabel *tiempoBronce = new QLabel("Menos de 02:45:00");
    tituloBronce->setAlignment(Qt::AlignCenter);
    tiempoBronce->setAlignment(Qt::AlignCenter);
    tituloBronce->setStyleSheet("color: #cd7f32; font-size: 15px; font-weight: bold; font-family: 'Arial Black'; background: transparent;");
    tiempoBronce->setStyleSheet("color: #ffffff; font-size: 13px; font-family: 'Arial'; background: transparent;");

    QFrame *frameBronce = new QFrame(widgetPodio);
    frameBronce->setStyleSheet("background-color: rgba(0,0,0,170); border-radius: 8px;");
    QVBoxLayout *layoutBronce = new QVBoxLayout(frameBronce);
    layoutBronce->setSpacing(5);
    layoutBronce->setContentsMargins(15, 10, 15, 10);
    layoutBronce->addWidget(medallaBronce);
    layoutBronce->addWidget(tituloBronce);
    layoutBronce->addWidget(tiempoBronce);

    layoutPodio->addWidget(frameOro);
    layoutPodio->addWidget(framePlata);
    layoutPodio->addWidget(frameBronce);
    widgetPodio->setLayout(layoutPodio);

    // Guardar referencias
    etiquetaTiempoOro    = tiempoOro;
    etiquetaTiempoPlata  = tiempoPlata;
    etiquetaTiempoBronce = tiempoBronce;
    etiquetaPodio        = widgetPodio;

    // ── Botón ─────────────────────────────────────────
    botonContinuar = new QPushButton("CONTINUAR", this);
    botonContinuar->setObjectName("botonContinuar");
    botonContinuar->setFixedSize(200, 60);
    botonContinuar->setCursor(Qt::PointingHandCursor);
    connect(botonContinuar, &QPushButton::clicked, this, &PantallaTransicion::continuar);

    layoutPrincipal->addWidget(etiquetaTitulo);
    layoutPrincipal->addWidget(etiquetaDescripcion);
    layoutPrincipal->addWidget(etiquetaImagen);
    layoutPrincipal->addWidget(widgetPodio);
    layoutPrincipal->addStretch();
    layoutPrincipal->addWidget(botonContinuar, 0, Qt::AlignCenter);

    setLayout(layoutPrincipal);
}

void PantallaTransicion::aplicarEstilos()
{
    setStyleSheet(R"(
        QLabel#etiquetaTitulo {
            color: #ffd700;
            font-size: 48px;
            font-weight: bold;
            font-family: "Arial Black", sans-serif;
            letter-spacing: 4px;
            background-color: rgba(0, 0, 0, 150);
            padding: 10px 20px;
            border-radius: 8px;
        }

        QLabel#etiquetaDescripcion {
            color: #ffffff;
            font-size: 22px;
            font-family: "Arial", sans-serif;
            padding: 10px 60px;
            background-color: rgba(0, 0, 0, 150);
            border-radius: 8px;
        }

        QPushButton#botonContinuar {
            background-color: rgba(0, 0, 0, 150);
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

void PantallaTransicion::establecerTexto(const QString &titulo, const QString &descripcion)
{
    etiquetaTitulo->setText(titulo);
    etiquetaDescripcion->setText(descripcion);
}

void PantallaTransicion::establecerModoFinal(bool esFinal)
{
    esModoFinal = esFinal;
    etiquetaImagen->setVisible(esFinal);
    etiquetaPodio->setVisible(esFinal);
    update();

    botonContinuar->disconnect();

    if (esFinal) {
        botonContinuar->setText("SALIR");
        connect(botonContinuar, &QPushButton::clicked, qApp, &QApplication::quit);
    } else {
        botonContinuar->setText("CONTINUAR");
        connect(botonContinuar, &QPushButton::clicked, this, &PantallaTransicion::continuar);
    }
}

void PantallaTransicion::establecerTiemposPodio(const QString &oro, const QString &plata, const QString &bronce)
{
    etiquetaTiempoOro->setText("Menos de " + oro);
    etiquetaTiempoPlata->setText("Menos de " + plata);
    etiquetaTiempoBronce->setText("Menos de " + bronce);
}

#include "pantallatransicion.moc"
