#ifndef RUNGAME_H
#define RUNGAME_H

#include <QWidget>
class QVBoxLayout;
class QHBoxLayout;
class QPushButton;
class QLabel;
class QGraphicsView;
class QGraphicsScene;

class runGame : public QWidget
{
    Q_OBJECT
    QHBoxLayout *layoutMain;
    QVBoxLayout *layoutLeft;
    QVBoxLayout *layoutRight;
    QLabel *lblplayerAndScore;
    QLabel *lblPlayerTurnAndRound;
    QPushButton* btnBackToMenu;
    QPushButton* btnNukeEverything;

    QGraphicsView *view;
    QGraphicsScene *scene;

    int numPlayers = 3;
    QVector<QLabel*> playerLabels;

    void setupConnects();
    void setupLayout();
    void redrawRightLayout();
    void redrawPexeso();

public:
    runGame(QWidget *parent = nullptr);

signals:
    void clickedBackToMenu();
};

#endif // RUNGAME_H
