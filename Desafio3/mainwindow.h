#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QStackedWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "nivel1.h"
#include "nivel2.h"
#include "pantallatransicion.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *evento)   override;
    void keyReleaseEvent(QKeyEvent *evento) override;

private slots:
    void onNivel1Terminado();
    void onContinuarTransicion();
    void onNivel2Terminado();

private:
    Ui::MainWindow     *ui;
    QStackedWidget     *stackedWidget;
    QGraphicsScene     *escena;
    QGraphicsView      *vistaJuego;
    Nivel1             *nivel1;
    Nivel2             *nivel2;
    PantallaTransicion *pantallaTransicion;

    static const int IDX_MENU       = 0;
    static const int IDX_JUEGO      = 1;
    static const int IDX_TRANSICION = 2;
};

#endif // MAINWINDOW_H
