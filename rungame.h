#ifndef RUNGAME_H
#define RUNGAME_H

#include <QWidget>
class QVBoxLayout;
class runGame : public QWidget
{
    QVBoxLayout *layoutMain;
public:
    runGame(QWidget *parent = nullptr);
};

#endif // RUNGAME_H
