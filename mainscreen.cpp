#include "mainscreen.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

MainScreen::MainScreen(QWidget *parent)
    : QWidget(parent)
{
    setupWindow(false);  // defaultně bez existující hry
    setupConnect();
}

void MainScreen::setupWindow(bool hasExistingGame)
{
    // tlačítka
    btnStartNewGame   = new QPushButton(tr("Start Game"));
    btnReturnToGame   = new QPushButton(tr("Return to Game"));
    btnSettings       = new QPushButton(tr("Settings"));
    btnQuit           = new QPushButton(tr("Quit"));

    // Return tlačítko aktivní jen pokud existuje hra
    btnReturnToGame->setEnabled(hasExistingGame);

    // stejná šířka
    const int btnWidth = 200;
    btnStartNewGame->setFixedWidth(btnWidth);
    btnReturnToGame->setFixedWidth(btnWidth);
    btnSettings->setFixedWidth(btnWidth);
    btnQuit->setFixedWidth(btnWidth);

    // padding + font
    const QString style = "font-size: 16px; padding: 10px 20px;";
    btnStartNewGame->setStyleSheet(style);
    btnReturnToGame->setStyleSheet(style);
    btnSettings->setStyleSheet(style);
    btnQuit->setStyleSheet(style);

    // layouty pro vycentrování
    lmaoyout = new QVBoxLayout(this);

    auto addCentered = [this](QPushButton* btn){
        auto *hl = new QHBoxLayout();
        hl->addStretch();
        hl->addWidget(btn);
        hl->addStretch();
        lmaoyout->addLayout(hl);
    };

    addCentered(btnStartNewGame);
    addCentered(btnReturnToGame);
    addCentered(btnSettings);
    addCentered(btnQuit);

    lmaoyout->addStretch();
    lmaoyout->setSpacing(15);
}

void MainScreen::setupConnect()
{
    connect(btnStartNewGame, &QPushButton::clicked, this, &MainScreen::clickedStartNewGame);
    connect(btnReturnToGame, &QPushButton::clicked, this, &MainScreen::clickedReturnToGame);
    connect(btnSettings, &QPushButton::clicked, this, &MainScreen::clickedSettings);
    connect(btnQuit, &QPushButton::clicked, this, &MainScreen::clickedQuit);
}

void MainScreen::setReturnButtonEnabled(bool enabled)
{
    if (btnReturnToGame) {
        btnReturnToGame->setEnabled(enabled);
    }
}
