#include "dlgsetting.h"
#include <QString>
#include <QComboBox>
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QSpinBox>
#include <QStringList>


dlgSetting::dlgSetting(unsigned int _baseMaxPl, int _baseSet, QWidget *parent)
    : maxPlayer(_baseMaxPl), QDialog(parent)
{
    setupWindow();
}

void dlgSetting::setupWindow()
{
    mainerLayout = new QVBoxLayout(this);
    mainLayout = new QHBoxLayout();
    playersLayout = new QVBoxLayout();
    everythingElseLayout = new QVBoxLayout();

    mainerLayout->addLayout(mainLayout);
    mainLayout->addLayout(playersLayout);
    mainLayout->addLayout(everythingElseLayout);

    for (unsigned int i = 0; i < maxPlayer; ++i) {
        QLineEdit *edit = new QLineEdit(this);
        edit->setPlaceholderText(tr("Player %1").arg(i + 1));
        playersLayout->addWidget(edit);
        LEplayers.append(edit);
    }
    LENumberOfCards = new QSpinBox(this);
    LENumberOfCards->setMinimum(2);
    LENumberOfCards->setMaximum(9);
    LENumberOfCards->setValue(2);
    everythingElseLayout->addWidget(LENumberOfCards);


    cbSet = new QComboBox(this);
    cbSet->addItem("Haha set");
    cbSet->addItem("Epic set");
    everythingElseLayout->addWidget(cbSet);


    buttonBox = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
        Qt::Horizontal, this
        );
    connect(buttonBox, &QDialogButtonBox::accepted, this, &dlgSetting::onAccept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &dlgSetting::reject);
    mainerLayout->addWidget(buttonBox);
}

std::vector<Plr> dlgSetting::getPlayersName() const
{
    std::vector<Plr> players;
    for (auto edit : LEplayers) {
        QString name = edit->text().trimmed();
        if (!name.isEmpty()) {
            players.emplace_back(name);
        }
    }
    return players;
}

QStringList dlgSetting::getCardSet() const
{
    switch (cbSet->currentIndex()) {
    case 0: return setOne;
    case 1: return setTwo;
    default: return setOne;
    }
}

unsigned int dlgSetting::getNumberOfCards() const
{
    return static_cast<unsigned int>(LENumberOfCards->value());
}

void dlgSetting::onAccept()
{
    accept();
}
