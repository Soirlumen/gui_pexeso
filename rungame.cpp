#include "rungame.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QString>

void runGame::setupConnects()
{
    connect(btnBackToMenu, &QPushButton::clicked, this, &runGame::clickedBackToMenu);
}

void runGame::setupLayout()
{
    // Hlavní horizontální layout
    layoutMain = new QHBoxLayout(this);

    // Levý panel (menu + hráči + info)
    layoutLeft = new QVBoxLayout();
    btnBackToMenu = new QPushButton(tr("Back to menu"));

    lblplayerAndScore = new QLabel(tr("players | score"));


    layoutLeft->addWidget(btnBackToMenu);
    layoutLeft->addWidget(lblplayerAndScore);
    QStringList playerNames = {"player1", "player2", "player3", "player4"};

    for (int i = 0; i < 4; ++i) {
        QLabel *lbl = new QLabel(this);

        if (i < numPlayers) {
            lbl->setText(QString("%1 | %2").arg(playerNames[i]).arg(0));
        } else {
            lbl->setText(" "); // placeholder
        }

        layoutLeft->addWidget(lbl);
        playerLabels.append(lbl);
    }

    lblPlayerTurnAndRound = new QLabel(
        tr("%1's turn | round: 0").arg(playerNames[0])
        );


    layoutLeft->addStretch(); // vyplní prázdný prostor
    layoutLeft->addWidget(lblPlayerTurnAndRound);

    // Pravý panel (hrací plocha + nuke button)
    layoutRight = new QVBoxLayout();
    view = new QGraphicsView();
    scene = new QGraphicsScene(this);
    view->setScene(scene);

    btnNukeEverything = new QPushButton(tr("DONT CLICK THIS OR IT BLOWS UP"));

    layoutRight->addWidget(view, 1); // 1 = expand
    layoutRight->addWidget(btnNukeEverything);

    // Spojení levého a pravého panelu
    layoutMain->addLayout(layoutLeft);
    layoutMain->addLayout(layoutRight);
}

runGame::runGame(QWidget *parent) {
    setupLayout();
    setupConnects();
}
