#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QKeyEvent>
#include "menu.h"
#include "nivel1.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *evento)   override;  // ← agregar
    void keyReleaseEvent(QKeyEvent *evento) override;  // ← agregar

private:
    Ui::MainWindow *ui;
    Nivel1 *nivel1;   // ← agregar
};
#endif // MAINWINDOW_H
