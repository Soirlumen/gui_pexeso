#include "rungame.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QString>

runGame::runGame(QWidget *parent) {

    layoutMain=new QVBoxLayout(this);
    btnBackToMenu=new QPushButton(tr("Back to main menu"));
    layoutMain->addWidget(btnBackToMenu);
    connect(btnBackToMenu, &QPushButton::clicked, this, &runGame::clickedBackToMenu);
}
