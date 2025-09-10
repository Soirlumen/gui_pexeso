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
    Pexeso pxs;

    const int cardSize = 100;

    // Stav hry
    int firstSelected = -1;    // index první odkryté karty
    int currentPlayer = 0;     // index hráče na tahu
    bool busy = false;         // blokuje klikání při čekání na otočení zpět
    QVector<CardItem*> cardItems; // reference na QGraphicsRectItem karty

    // Interní funkce
    void setupConnects();
    void setupLayout();
    void redrawRightLayout();
    void drawPexeso();
    void updatePlayerScores();
    void revealCard(int index);
    void updateCards();

public:
    runGame(QWidget *parent = nullptr);

public slots:
    void cardClicked(int index);

signals:
    void clickedBackToMenu();
};

#endif // RUNGAME_H
