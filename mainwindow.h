#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include "mainscreen.h"
#include "dlgsetting.h"
#include "rungame.h"

class QStackedWidget;
class QString;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QStackedWidget *stack;
    MainScreen *mscreen;

    runGame *rGame;
    QStringList pendingCardSet;
    std::vector<Plr> pendingPlayers;
    unsigned int pendingNumCards = 0;
    bool settingsReady = false;

    QString workdir;
    dlgSetting *dlg;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setupThingy();

protected:
    void closeEvent(QCloseEvent *event) override;

public slots:
    void startNewGame();
    void startExistingGame();
    void openSettings();
    void backToMenu();
};
#endif // MAINWINDOW_H
