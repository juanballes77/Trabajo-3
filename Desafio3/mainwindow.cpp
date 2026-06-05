#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "menu.h"
#include "nivel1.h"
#include <QStackedWidget>
#include <QGraphicsView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // ── Ventana maximizada primero ──────────────────
    showMaximized();

    // ── Stacked Widget ──────────────────────────────
    QStackedWidget *stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);

    // ── Escena y vista del juego ────────────────────
    QGraphicsScene *escena = new QGraphicsScene(this);
    QGraphicsView  *vistaJuego = new QGraphicsView(escena, this);

    // Quitar scrollbars
    vistaJuego->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    vistaJuego->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // La vista escala el contenido para llenar el widget
    vistaJuego->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    // ── Menú ────────────────────────────────────────
    Menu *menu = new Menu();
    stackedWidget->addWidget(menu);       // índice 0 → menú
    stackedWidget->addWidget(vistaJuego); // índice 1 → juego

    // ── Nivel 1 ─────────────────────────────────────
    nivel1 = new Nivel1(escena, this);

    // ── Conexión: botón jugar → iniciar nivel ───────
    connect(menu, &Menu::jugarPresionado, this, [=]() {
        stackedWidget->setCurrentIndex(1);

        // Ajustar escena al tamaño real de la vista una vez visible
        QRectF rect = vistaJuego->rect();
        escena->setSceneRect(0, 0, rect.width(), rect.height());
        vistaJuego->fitInView(escena->sceneRect(), Qt::IgnoreAspectRatio);

        nivel1->iniciar();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *evento)
{
    nivel1->teclaPresionada(evento);
}

void MainWindow::keyReleaseEvent(QKeyEvent *evento)
{
    nivel1->teclaLiberada(evento);
}
