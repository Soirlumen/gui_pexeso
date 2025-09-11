#ifndef PEXESO_H
#define PEXESO_H

#include "gameboard.h"
#include "Player.h"
typedef Player<Str> Plr;

class Pexeso
{
private:
    std::vector<Plr> players;
    Gameboard Gme;
    unsigned int round;

public:
    static constexpr int MAX_PLAYERS = 4;
    Pexeso(std::vector<Plr> _p, Gameboard _g);
    bool oneTurn(Plr &_player, const int first_card, const int second_card);
    void oneRound();
    bool isAllGone() const;
    ~Pexeso();
    Gameboard &getGme() { return Gme; }
    const Gameboard &getGme() const { return Gme; }
    const std::vector<Plr> &getPlayers() const;
    std::vector<Plr> &getPlayers();
    unsigned int getRound() const;
    int getACardIndex() const;
    void setRound(unsigned int _nr);

    void addRound()
    {
        setRound(getRound() + 1);
    }
    void showResults() const;
    void play();
};

#endif
