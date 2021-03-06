#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QtGui>
#include <QVBoxLayout>
#include <QSound>
#include "graphicsview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QPushButton *btnStart;
    QPushButton *btnAbout;
    QPushButton *btnExit;
    QPixmap *bkgnd;
    QPixmap *about;
    QPixmap *def_img;
    QPixmap *vic_img;
    QVBoxLayout* layout;
    GraphicsView *view;
    QSound *music;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void drawMenu();
    void drawAbout();
    void startGame();
    void setVictory();
    void setDefeat();
    void setStyle(QPushButton* btn);

public slots:
    void goToAbout();
    void goToMenu();
    void goToMenuFromGame();
    void victory();
    void defeat();
    void goToGame();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
