#include "mainwindow.h"
#include <QStackedWidget>
#include <QString>
#include <QMessageBox>
#include <QCloseEvent>

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


    connect(mscreen, &MainScreen::clickedStartNewGame,
            this, &MainWindow::startNewGame);

}

void MainWindow::startNewGame()
{
    stack->setCurrentIndex(1);

}

void MainWindow::startExistingGame()
{

}

void MainWindow::openSettings()
{

}

void MainWindow::backToMenu()
{

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
