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
#include <QMessageBox>
#include <QTimer>

void runGame::setupConnects()
{
    connect(btnBackToMenu, &QPushButton::clicked, this, &runGame::clickedBackToMenu);
}

void runGame::setupMainLayout()
{
    layoutMain = new QHBoxLayout(this);
    layoutMain->addLayout(setupLeftLayout());
    layoutMain->addLayout(setupRightLayout());
}

QVBoxLayout* runGame::setupLeftLayout()
{
    layoutLeft = new QVBoxLayout();
    btnBackToMenu = new QPushButton(tr("Back to menu"));
    layoutLeft->addWidget(btnBackToMenu);

    lblplayerAndScore = new QLabel(tr("players | score"));
    layoutLeft->addWidget(lblplayerAndScore);

    setupPlayerLabels();
    layoutLeft->addStretch();
    lblPlayerTurnAndRound = new QLabel(
        tr("%1's turn | round: 0").arg(pxs->getPlayers()[0].getName())
        );
    layoutLeft->addWidget(lblPlayerTurnAndRound);

    return layoutLeft;
}

void runGame::setupPlayerLabels()
{
    const auto &players = pxs->getPlayers();
    playerLabels.clear();
    for (size_t i = 0; i < players.size(); ++i) {
        QLabel *lbl = new QLabel(this);
        lbl->setText(QString("%1 | %2").arg(players[i].getName()).arg(players[i].getScore()));
        layoutLeft->addWidget(lbl);
        playerLabels.append(lbl);
    }
    for (size_t i = players.size(); i < 4; ++i) {
        QLabel *lbl = new QLabel(" ", this);
        layoutLeft->addWidget(lbl);
        playerLabels.append(lbl);
    }
}

QVBoxLayout* runGame::setupRightLayout()
{
    layoutRight = new QVBoxLayout();
    view = new QGraphicsView();
    scene = new QGraphicsScene(this);
    view->setScene(scene);

    btnNukeEverything = new QPushButton(tr("DONT CLICK THIS OR IT BLOWS UP"));
    layoutRight->addWidget(view, 1);
    layoutRight->addWidget(btnNukeEverything);

    return layoutRight;
}

void runGame::drawPexeso()
{
    scene->clear();
    cardItems.clear();
    const auto &deck = pxs->getGme().getDeck();
    int x = 0, y = 0;
    const int spacing = 0;

    for (size_t i = 0; i < deck.size(); ++i) {
        auto *rect = createCardItem(static_cast<int>(i), x, y);
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

CardItem* runGame::createCardItem(int index, int x, int y)
{
    auto *rect = new CardItem(index);
    rect->setRect(x, y, cardSize, cardSize);
    rect->setBrush(pxs->getGme().getDeck()[index].isVisible() ? Qt::white : Qt::gray);
    rect->setPen(QPen(Qt::black));
    return rect;
}

void runGame::cardClicked(int index)
{
    auto &deck = pxs->getGme().getDeck();
    if (deck[index].isVisible() || busy) return;

    revealcard(index);
    updateCards();

    if (firstSelected == -1) {
        firstSelected = index;
        return;
    }

    handleSecondCard(index);
}

runGame::~runGame()
{
 delete pxs;
}

void runGame::handleSecondCard(int secondSelected)
{
    Plr &player = pxs->getPlayers()[currentPlayer];
    busy = true;

    bool match = pxs->oneTurn(player, firstSelected, secondSelected);
    updatePlayerScores();
    updateCards();

    if (!match) {
        handleNonMatchingCards(firstSelected, secondSelected);
    } else {
        busy = false;
    }

    updateGameState();
    firstSelected = -1;

    // ---- kontrola konce hry zde ----
    if (pxs->isAllGone()) {
        QString resultText;
        for (const auto &p : pxs->getPlayers()) {
            resultText += QString("%1: %2\n").arg(p.getName()).arg(p.getScore());
        }
        QMessageBox::information(this, tr("Game Over!"), resultText);
    }
}


void runGame::handleNonMatchingCards(int first, int second)
{
    QTimer::singleShot(800, this, [this, first, second]() {
        auto &deck = pxs->getGme().getDeck();
        deck[first].flipCard();
        deck[second].flipCard();
        updateCards();
        busy = false;
    });
}

void runGame::updateGameState()
{
    currentPlayer = (currentPlayer + 1) % pxs->getPlayers().size();
    if (currentPlayer == 0) {
        pxs->addRound();
    }
    lblPlayerTurnAndRound->setText(
        QString("%1's turn | round: %2")
            .arg(pxs->getPlayers()[currentPlayer].getName())
            .arg(pxs->getRound())
        );
}

void runGame::updatePlayerScores()
{
    for (int i = 0; i < pxs->getPlayers().size(); ++i) {
        playerLabels[i]->setText(QString("%1 | %2").arg(pxs->getPlayers()[i].getName()).arg(pxs->getPlayers()[i].getScore()));
    }
}

void runGame::revealcard(int index)
{
    auto &deck = pxs->getGme().getDeck();
    if (!deck[index].isVisible()) {
        deck[index].flipCard();
    }
}

void runGame::updateCards()
{
    const auto &deck = pxs->getGme().getDeck();
    const int margin = 3; // tloušťka vnitřního rámečku

    for (int i = 0; i < cardItems.size(); ++i) {
        CardItem *item = cardItems[i];

        if (deck[i].isVisible()) {
            QString path = deck[i].getPicca();
            QPixmap pix(path);

            // vytvoř finální pixmapu se stejnou velikostí jako karta
            QPixmap finalPixmap(cardSize, cardSize);
            finalPixmap.fill(Qt::black); // černý rámeček

            QPainter painter(&finalPixmap);
            // nakresli obrázek uvnitř s marginem
            painter.drawPixmap(margin, margin,
                               cardSize - 2*margin,
                               cardSize - 2*margin,
                               pix);
            painter.end();

            item->setBrush(QBrush(finalPixmap));
        } else {
            // zakrytá karta
            QPixmap cover(cardSize, cardSize);
            cover.fill(Qt::black);
            QPainter painter(&cover);
            painter.fillRect(margin, margin, cardSize - 2*margin, cardSize - 2*margin, Qt::gray);
            painter.end();
            item->setBrush(QBrush(cover));
        }
    }
}

bool runGame::allCardsRevealed() const
{
    const auto &deck = pxs->getGme().getDeck();
    for (const auto &card : deck) {
        if (!card.isVisible()) return false;
    }
    return true;
}

runGame::runGame(QWidget *parent)
    :  QWidget(parent), players({ Plr("playernbnrgj1"), Plr("player2") })
{
    pxs = new Pexeso(players, Gameboard(setOne, 5));
    setupMainLayout();
    setupConnects();
    drawPexeso();
}

runGame::runGame(QStringList _cardSet, std::vector<Plr> _plrs, unsigned int _numberOfCards, QWidget *parent):QWidget(parent),players(_plrs), cardSet(_cardSet),
    numberOfCards(_numberOfCards)
{
    pxs=new Pexeso(players,Gameboard(cardSet, numberOfCards));
    setupMainLayout();
    setupConnects();
    drawPexeso();
}

void runGame::resetGame()
{
    delete pxs;

    // vytvoříme nový
    pxs = new Pexeso(players, Gameboard(cardSet, numberOfCards));

    // obnovíme GUI
    updatePlayerScores();
    drawPexeso();

    // reset aktuálního hráče a kola
    currentPlayer = 0;
    lblPlayerTurnAndRound->setText(
        QString("%1's turn | round: %2")
            .arg(pxs->getPlayers()[currentPlayer].getName())
            .arg(pxs->getRound())
        );
}
