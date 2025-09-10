#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include "mainscreen.h"
#include "rungame.h"


class QStackedWidget;
class QString;


class MainWindow : public QMainWindow
{
    Q_OBJECT
    QStackedWidget *stack;
    MainScreen *mscreen;
    runGame* rGame;

    QString workdir;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setupThingy();

protected:
    void closeEvent(QCloseEvent *event) override;

public slots:
    void startNewGame();
    //void startExistingGame();
    void openSettings();
    void backToMenu();
};
#endif // MAINWINDOW_H
