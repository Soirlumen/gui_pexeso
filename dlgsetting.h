#ifndef DLGSETTING_H
#define DLGSETTING_H

#include <QDialog>
#include <QVector>
#include "pexeso.h"
#include "cardSets.h"

class QString;
class QComboBox;
class QLineEdit;
class QLabel;
class QHBoxLayout;
class QVBoxLayout;
class QDialogButtonBox;
class QSpinBox;

class dlgSetting : public QDialog
{
    Q_OBJECT
    QLabel *lblSet;
    QLabel *lblPlNames;
    QComboBox *cbSet;
    QVector<QLineEdit*> LEplayers;
    QSpinBox *LENumberOfCards;

    QVBoxLayout *mainerLayout;
    QHBoxLayout *mainLayout;
    QVBoxLayout *playersLayout;
    QVBoxLayout *everythingElseLayout;

    unsigned int maxPlayer;

    QDialogButtonBox *buttonBox;

public:
    dlgSetting(unsigned int _baseMaxPl = 4, int _baseSet = 0, QWidget *parent = nullptr);
    void setupWindow();

    std::vector<Plr> getPlayersName() const;
    QStringList getCardSet() const;
    unsigned int getNumberOfCards() const;

private slots:
    void onAccept();
};

#endif // DLGSETTING_H
