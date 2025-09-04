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
    connect(mscreen, &MainScreen::clickedStartExistingGame, this, &MainWindow::startExistingGame);
    connect(mscreen, &MainScreen::clickedSettings, this, &MainWindow::openSettings);
    connect(rGame, &runGame::clickedBackToMenu, this, &MainWindow::backToMenu);

}

void MainWindow::startNewGame()
{
    stack->setCurrentIndex(1);

}

void MainWindow::startExistingGame()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    workdir,
                                                    tr("Plain text (*.txt)"));
    if (!fileName.isEmpty())
    {
        QFileInfo info(fileName);
        workdir = info.absoluteDir().absolutePath();
        //loadGame(read_file2(fileName), symbolforlivecell);
    }
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
