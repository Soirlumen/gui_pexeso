#ifndef RUNGAME_H
#define RUNGAME_H

#include <QWidget>
#include <QVector>
#include "pexeso.h"
#include "CardItem.h"

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

    // Layouty
    QHBoxLayout *layoutMain;
    QVBoxLayout *layoutLeft;
    QVBoxLayout *layoutRight;

    // Levý panel – hráči
    QLabel *lblplayerAndScore;
    QLabel *lblPlayerTurnAndRound;
    QVector<QLabel*> playerLabels;

    // Tlačítka
    QPushButton* btnBackToMenu;
    QPushButton* btnNukeEverything;

    // Hrací plocha
    QGraphicsView *view;
    QGraphicsScene *scene;

    // Hra
    Gameboard gameboard;
    Pexeso *pxs;

    const int cardSize = 150;

    // Stav hry
    int firstSelected = -1;
    int currentPlayer = 0;
    bool busy = false;
    QVector<CardItem*> cardItems;

    // Interní funkce
    void setupConnects();
    void setupMainLayout();
    QVBoxLayout* setupLeftLayout();
    void setupPlayerLabels();
    QVBoxLayout* setupRightLayout();
    void drawPexeso();
    CardItem* createCardItem(int index, int x, int y);
    void updatePlayerScores();
    void revealCard(int index);
    void updateCards();
    void handleSecondCard(int secondSelected);
    void handleNonMatchingCards(int first, int second);
    void updateGameState();
    bool allCardsRevealed() const;

public:
    runGame(QWidget *parent = nullptr);
 void resetGame();
    ~runGame();
public slots:
    void cardClicked(int index);


signals:
    void clickedBackToMenu();
};

#endif // RUNGAME_H
