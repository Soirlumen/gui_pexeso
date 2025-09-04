#include "mainscreen.h"
#include <QPushButton>
#include <QVBoxLayout>

MainScreen::MainScreen(QWidget *parent) {
    setupWindow();
    setupConnect();
}

void MainScreen::setupWindow()
{
    btnStartNewGame = new QPushButton(tr("Start Game"));
    btnStartExistingGame  = new QPushButton(tr("Load Game"));
    btnSettings= new QPushButton(tr("Settings"));
    btnQuit  = new QPushButton(tr("Quit"));
    lmaoyout =new QVBoxLayout(this);
    lmaoyout->addWidget(btnStartNewGame);
    lmaoyout->addWidget(btnStartExistingGame);
    lmaoyout->addWidget(btnSettings);
    lmaoyout->addWidget(btnQuit);
}


void MainScreen::setupConnect()
{
    connect(btnStartNewGame, &QPushButton::clicked,
            this, &MainScreen::clickedStartNewGame);


}
