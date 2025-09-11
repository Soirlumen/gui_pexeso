#include "mainwindow.h"
#include <QStackedWidget>
#include <QString>
#include <QMessageBox>
#include <QCloseEvent>
#include <QFileDialog>
#include <QFileInfo>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupThingy();
}

MainWindow::~MainWindow() {}

void MainWindow::setupThingy()
{
    stack=new QStackedWidget();
    mscreen=new MainScreen(this);
    rGame=new runGame(this);
    stack->addWidget(mscreen);
    stack->addWidget(rGame);
    setCentralWidget(stack);
    stack->setCurrentIndex(0);


    connect(mscreen, &MainScreen::clickedStartNewGame, this, &MainWindow::startNewGame);
    connect(mscreen, &MainScreen::clickedReturnToGame, this, &MainWindow::startExistingGame);
    connect(mscreen, &MainScreen::clickedSettings, this, &MainWindow::openSettings);
    connect(rGame, &runGame::clickedBackToMenu, this, &MainWindow::backToMenu);
    connect(mscreen, &MainScreen::clickedQuit, this, &QWidget::close);

}

void MainWindow::startNewGame()
{    rGame->resetGame(); // pokud máš metodu pro reset hry

    // přepnutí na hru
    stack->setCurrentIndex(1);

    // aktivace Return tlačítka
    mscreen->setReturnButtonEnabled(true);
}
void MainWindow::startExistingGame()
{
 stack->setCurrentIndex(1);
}


void MainWindow::openSettings()
{

}

void MainWindow::backToMenu()
{
stack->setCurrentIndex(0);
}

void MainWindow::closeEvent(QCloseEvent *evt)
{
    if (QMessageBox::question(this, tr("odeYEET?"), tr("chcete fakt ukoncit appku!? : (")) == QMessageBox::StandardButton::No)
    {
        evt->ignore();
        return;
    }
    evt->accept();
}
