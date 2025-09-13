#ifndef RUNGAME_H
#define RUNGAME_H

#include <QWidget>
#include <vector>
#include "pexeso.h"
#include "CardItem.h"
#include "cardSets.h"

class QVBoxLayout;
class QHBoxLayout;
class QPushButton;
class QLabel;
class QGraphicsView;
class QGraphicsScene;
class CardItem;

class runGame : public QWidget
{
    Q_OBJECT

    QHBoxLayout *layoutMain;
    QVBoxLayout *layoutLeft;
    QVBoxLayout *layoutRight;

    QLabel *lblplayerAndScore;
    QLabel *lblPlayerTurnAndRound;
    QVector<QLabel*> playerLabels;
    QPushButton* btnBackToMenu;
    QPushButton* btnNukeEverything;

    QGraphicsView *view;
    QGraphicsScene *scene;

    Pexeso *pxs;
    std::vector<Plr> players;
    QStringList cardSet;
    unsigned int numberOfCards;

    const int cardSize = 150;

    int firstSelected = -1;
    int currentPlayer = 0;
    bool busy = false;
    QVector<CardItem*> cardItems;

    void setupConnects();
    void setupMainLayout();
    QVBoxLayout* setupLeftLayout();
    void setupPlayerLabels();
    QVBoxLayout* setupRightLayout();
    void drawPexeso();
    CardItem* createCardItem(int index, int x, int y);
    void updatePlayerScores();
    void revealcard(int index);
    void updateCards();
    void handleSecondCard(int secondSelected);
    void handleNonMatchingCards(int first, int second);
    void updateGameState();
    bool allCardsRevealed() const;

public:
    runGame(QWidget *parent = nullptr);
    runGame(QStringList _cardSet, std::vector<Plr> _plrs={Plr("playernbnrgj1"), Plr("player2")},  unsigned int _numberOfCards=5,QWidget *parent = nullptr);
 void resetGame();
    ~runGame();
public slots:
    void cardClicked(int index);


signals:
    void clickedBackToMenu();
};

#endif // RUNGAME_H
