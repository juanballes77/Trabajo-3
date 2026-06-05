#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "menu.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
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
        "Has terminado la etapa de natación.\n¡Prepárate para el ciclismo!"
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
        escena->setSceneRect(0, 0, rect.width(), rect.height()); // ← escena cuadrada para nivel 2
        vistaJuego->resetTransform();
        vistaJuego->fitInView(escena->sceneRect(), Qt::IgnoreAspectRatio);

        nivel2->iniciar(); // ← nivel2 en lugar de nivel1
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
    // Texto de transición entre niveles
    pantallaTransicion->establecerTexto(
        "¡ETAPA 1 COMPLETADA!",
        "Has terminado la etapa de natación.\n¡Prepárate para el ciclismo!"
        );
    stackedWidget->setCurrentIndex(IDX_TRANSICION);
}

void MainWindow::onContinuarTransicion()
{
    // Si el nivel 2 ya terminó, volver al menú
    if (nivel2->obtenerNivelCompletado()) {
        stackedWidget->setCurrentIndex(IDX_MENU);
        return;
    }

    // Si no, iniciar nivel 2
    QRectF rect = vistaJuego->rect();
    escena->setSceneRect(0, 0, rect.width(), rect.height());
    vistaJuego->resetTransform();
    vistaJuego->fitInView(escena->sceneRect(), Qt::IgnoreAspectRatio);

    stackedWidget->setCurrentIndex(IDX_JUEGO);
    nivel2->iniciar();
}

void MainWindow::onNivel2Terminado()
{
    // Reutilizar pantalla de transición como pantalla final
    pantallaTransicion->establecerTexto(
        "¡TRIATLÓN COMPLETADO!",
        "¡Felicitaciones!\nHas completado las etapas de\nnatación y ciclismo."
        );
    stackedWidget->setCurrentIndex(IDX_TRANSICION);
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
