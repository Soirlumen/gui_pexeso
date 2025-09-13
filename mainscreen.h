#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <QWidget>

class QPushButton;
class QVBoxLayout;

class MainScreen : public QWidget
{
    Q_OBJECT

    QPushButton* btnStartNewGame;
    QPushButton* btnReturnToGame;
    QPushButton* btnSettings;
    QPushButton* btnQuit;

    QVBoxLayout* lmaoyout;

public:
    MainScreen(QWidget *parent = nullptr);
    void setNewGameButtonEnabled(bool enabled);
    void setReturnButtonEnabled(bool enabled);
    void setupWindow(bool hasExistingGame = false);
    void setupConnect();

signals:
    void clickedStartNewGame();
    void clickedReturnToGame();
    void clickedSettings();
    void clickedQuit();
};

#endif // MAINSCREEN_H
