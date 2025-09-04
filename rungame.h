#ifndef RUNGAME_H
#define RUNGAME_H

#include <QWidget>
class QVBoxLayout;
class QPushButton;
class runGame : public QWidget
{
    Q_OBJECT
    QVBoxLayout *layoutMain;
    QPushButton* btnBackToMenu;
public:
    runGame(QWidget *parent = nullptr);

signals:
    void clickedBackToMenu();
};

#endif // RUNGAME_H
