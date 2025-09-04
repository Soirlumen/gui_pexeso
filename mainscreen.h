#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <QWidget>

class QPushButton;
class QVBoxLayout;
class MainScreen : public QWidget
{
Q_OBJECT
    QPushButton* btnStartNewGame;
    QPushButton* btnStartExistingGame;
    QPushButton* btnSettings;
    QPushButton* btnQuit;
    QVBoxLayout* lmaoyout;

public:
    MainScreen(QWidget *parent = nullptr);
    void setupWindow();
    void setupConnect();


signals:
    void clickedStartNewGame();
    void clickedStartExistingGame();
    void clickedSettings();
    void clickedQuit();
public slots:
};

#endif // MAINSCREEN_H
