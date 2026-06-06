#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "menu.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , tiempoAcumulado(0)
{
    ui->setupUi(this);

    showMaximized();

    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);

    escena     = new QGraphicsScene(this);
    vistaJuego = new QGraphicsView(escena, this);
    vistaJuego->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    vistaJuego->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    vistaJuego->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    // ── Pantallas ────────────────────────────────────
    Menu *menu = new Menu();
    pantallaTransicion = new PantallaTransicion(this);
    pantallaTransicion->establecerTexto(
        "¡ETAPA 1 COMPLETADA!",
        "Has terminado la etapa de natación.\n\nAhora pasas a tierra firme. Esquiva a los demás\nciclistas y obstáculos para llegar en primer lugar."
        );

    stackedWidget->addWidget(menu);               // índice 0 → menú
    stackedWidget->addWidget(vistaJuego);         // índice 1 → juego
    stackedWidget->addWidget(pantallaTransicion); // índice 2 → transición

    // ── Niveles ──────────────────────────────────────
    nivel1 = new Nivel1(escena, this);
    nivel2 = new Nivel2(escena, this);

    // ── Conexiones ───────────────────────────────────
    connect(menu, &Menu::jugarPresionado, this, [=]() {
        stackedWidget->setCurrentIndex(IDX_JUEGO);

        QRectF rect = vistaJuego->rect();
        escena->setSceneRect(0, 0, 10000, rect.height());
        vistaJuego->resetTransform();

        // Iniciar cronómetro
        tiempoAcumulado = 0;
        cronometro.restart();

        nivel1->iniciar();
    });

    connect(nivel1, &Nivel1::nivelTerminado, this, &MainWindow::onNivel1Terminado);
    connect(nivel2, &Nivel2::nivelTerminado, this, &MainWindow::onNivel2Terminado);
    connect(pantallaTransicion, &PantallaTransicion::continuar, this, &MainWindow::onContinuarTransicion);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ─── Slots ────────────────────────────────────────────────────

void MainWindow::onNivel1Terminado()
{
    // Pausar cronómetro
    tiempoAcumulado += cronometro.elapsed();

    nivel1->terminar();

    pantallaTransicion->establecerModoFinal(false);
    pantallaTransicion->establecerTexto(
        "¡ETAPA 1 COMPLETADA!",
        "Has terminado la etapa de natación.\n\nAhora pasas a tierra firme. Esquiva a los demás\nciclistas y obstáculos para llegar en primer lugar."
        );
    stackedWidget->setCurrentIndex(IDX_TRANSICION);
}

void MainWindow::onContinuarTransicion()
{
    if (nivel2->obtenerNivelCompletado()) {
        stackedWidget->setCurrentIndex(IDX_MENU);
        return;
    }

    QRectF rect = vistaJuego->rect();
    escena->setSceneRect(0, 0, rect.width(), rect.height());
    vistaJuego->resetTransform();
    vistaJuego->fitInView(escena->sceneRect(), Qt::IgnoreAspectRatio);

    stackedWidget->setCurrentIndex(IDX_JUEGO);

    // Reanudar cronómetro
    cronometro.restart();

    nivel2->iniciar();
}

void MainWindow::onNivel2Terminado()
{
    tiempoAcumulado += cronometro.elapsed();
    QString tiempoTotal = formatearTiempo(tiempoAcumulado);

    // Determinar puesto según tiempo
    QString puesto;
    if (tiempoAcumulado < 142000)      // menos de 2:22:00
        puesto = "¡primer lugar! 🥇";
    else if (tiempoAcumulado < 156000) // menos de 2:36:00
        puesto = "¡segundo lugar! 🥈";
    else if (tiempoAcumulado < 165000) // menos de 2:45:00
        puesto = "¡tercer lugar! 🥉";
    else
        puesto = "fuera del podio";

    pantallaTransicion->establecerModoFinal(true);
    pantallaTransicion->establecerTiemposPodio("02:22:00", "02:36:00", "02:45:00");
    pantallaTransicion->establecerTexto(
        "¡TRIATLÓN COMPLETADO!",
        QString("¡Felicitaciones! Has quedado en %1\n\nTiempo total: %2").arg(puesto).arg(tiempoTotal)
        );
    stackedWidget->setCurrentIndex(IDX_TRANSICION);
}

QString MainWindow::formatearTiempo(qint64 ms)
{
    qint64 segundos     = ms / 1000;
    qint64 minutos      = segundos / 60;
    segundos            = segundos % 60;
    qint64 milisegundos = (ms % 1000) / 10;

    return QString("%1:%2:%3")
        .arg(minutos,      2, 10, QChar('0'))
        .arg(segundos,     2, 10, QChar('0'))
        .arg(milisegundos, 2, 10, QChar('0'));
}

// ─── Teclado ──────────────────────────────────────────────────

void MainWindow::keyPressEvent(QKeyEvent *evento)
{
    if (stackedWidget->currentIndex() == IDX_JUEGO) {
        nivel1->teclaPresionada(evento);
        nivel2->teclaPresionada(evento);
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *evento)
{
    if (stackedWidget->currentIndex() == IDX_JUEGO) {
        nivel1->teclaLiberada(evento);
        nivel2->teclaLiberada(evento);
    }
}
