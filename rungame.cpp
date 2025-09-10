#include "rungame.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QStringList>
#include <QBrush>
#include <QPen>
#include <QDebug>
#include <QTimer>


static const QStringList setOne {
    ":/baseset/pic/1.png",
    ":/baseset/pic/2.png",
    ":/baseset/pic/3.png",
    ":/baseset/pic/4.png",
    ":/baseset/pic/5.png",
    ":/baseset/pic/6.png",
    ":/baseset/pic/7.png",
    ":/baseset/pic/8.png",
    ":/baseset/pic/9.png"
};

static const QStringList setTwo {
    ":/epicset/lol/1.jpg",
    ":/epicset/lol/2.jpg",
    ":/epicset/lol/3.jpg",
    ":/epicset/lol/4.jpg",
    ":/epicset/lol/5.jpg",
    ":/epicset/lol/6.jpg",
    ":/epicset/lol/7.jpg",
    ":/epicset/lol/8.jpg",
    ":/epicset/lol/9.jpg",
    ":/epicset/lol/10.jpg",
    ":/epicset/lol/11.jpg",
    ":/epicset/lol/12.jpg",
    ":/epicset/lol/13.jpg",
    ":/epicset/lol/14.jpg",
    ":/epicset/lol/15.jpg"
};

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
    layoutLeft->addWidget(btnBackToMenu);

    lblplayerAndScore = new QLabel(tr("players | score"));
    layoutLeft->addWidget(lblplayerAndScore);

    // Vykreslení hráčů podle pxs
    const auto &players = pxs.getPlayers();
    playerLabels.clear();
    for (size_t i = 0; i < players.size(); ++i) {
        QLabel *lbl = new QLabel(this);
        lbl->setText(QString("%1 | %2").arg(players[i].getName()).arg(players[i].getScore()));
        layoutLeft->addWidget(lbl);
        playerLabels.append(lbl);
    }

    // Pokud chceš mít max 4 labely, doplníme prázdné místo
    for (size_t i = players.size(); i < 4; ++i) {
        QLabel *lbl = new QLabel(" ", this);
        layoutLeft->addWidget(lbl);
        playerLabels.append(lbl);
    }

    lblPlayerTurnAndRound = new QLabel(
        tr("%1's turn | round: 0").arg(players[0].getName())
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

void runGame::drawPexeso()
{
    scene->clear();
    cardItems.clear();
    const auto &deck = pxs.getGme().getDeck();
    int x = 0, y = 0;
    const int spacing = 5;

    for (size_t i = 0; i < deck.size(); ++i) {
        auto *rect = new CardItem(static_cast<int>(i));
        rect->setRect(x, y, cardSize, cardSize);
        rect->setBrush(deck[i].isVisible() ? Qt::white : Qt::gray);
        rect->setPen(QPen(Qt::black));

        scene->addItem(rect);
        cardItems.append(rect);

        connect(rect, &CardItem::clicked, this, &runGame::cardClicked);

        x += cardSize + spacing;
        if (x + cardSize > view->width()) {
            x = 0;
            y += cardSize + spacing;
        }
    }
}


void runGame::cardClicked(int index)
{
    auto &deck = pxs.getGme().getDeck();

    // Ignorujeme klik na již odkrytou kartu nebo pokud jsme "busy"
    if (deck[index].isVisible() || busy) return;

    // Odkryjeme kartu a aktualizujeme zobrazení
    revealCard(index);
    updateCards();

    if (firstSelected == -1) {
        // První karta v páru
        firstSelected = index;
        return;
    }

    // Druhá karta v páru
    int secondSelected = index;
    Plr &player = pxs.getPlayers()[currentPlayer];

    // Zablokujeme klikání během vyhodnocení
    busy = true;

    // Vyhodnotíme pár (vrací true, pokud se ID shodují)
    bool match = pxs.oneTurn(player, firstSelected, secondSelected);

    // Aktualizujeme skóre a karty
    updatePlayerScores();
    updateCards();

    if (!match) {
        // Pokud se karty neshodují, otočíme je zpět po 0.8s
        int first = firstSelected;
        int second = secondSelected;
        QTimer::singleShot(800, this, [this, first, second]() {
            auto &deck = pxs.getGme().getDeck();
            deck[first].flipCard();
            deck[second].flipCard();
            updateCards();
            busy = false; // odblokujeme klikání
        });
    } else {
        // Pokud je pár, karty zůstanou odkryté a body jsou přičteny
        busy = false;
    }

    // Přepneme hráče a aktualizujeme label s jeho kolem
    currentPlayer = (currentPlayer + 1) % pxs.getPlayers().size();
    lblPlayerTurnAndRound->setText(
        QString("%1's turn | round: %2")
            .arg(pxs.getPlayers()[currentPlayer].getName())
            .arg(pxs.getRound())
        );

    // Resetujeme první vybranou kartu pro další tah
    firstSelected = -1;
}


void runGame::updatePlayerScores()
{
    for (int i = 0; i < pxs.getPlayers().size(); ++i) {
        playerLabels[i]->setText(QString("%1 | %2").arg(pxs.getPlayers()[i].getName()).arg(pxs.getPlayers()[i].getScore()));
    }
}


void runGame::revealCard(int index)
{
    auto &deck = pxs.getGme().getDeck();
    if (!deck[index].isVisible()) {
        deck[index].flipCard();
    }
}

void runGame::updateCards()
{
    const auto &deck = pxs.getGme().getDeck();
    for (int i = 0; i < cardItems.size(); ++i) {
        if (deck[i].isVisible()) {
            // Získáme cestu k obrázku podle ID karty
            QString path = deck[i].getPicca(); // musíš mít metodu getImagePath() ve třídě Card
            QPixmap pix(path);
            cardItems[i]->setBrush(QBrush(pix.scaled(cardSize, cardSize))); // přizpůsobíme velikost karty
        } else {
            cardItems[i]->setBrush(Qt::gray); // zakrytá karta
        }
    }
}



runGame::runGame(QWidget *parent)
    : QWidget(parent), gameboard(setOne, 5), pxs({ Plr("playernbnrgj1"), Plr("player2") }, gameboard)
{
    setupLayout();
    setupConnects();
    drawPexeso();
}
