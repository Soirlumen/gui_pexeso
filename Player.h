#ifndef PLAYER_H
#define PLAYER_H
#include <string>
template<typename T>
class Player
{

private:
    T name;
    unsigned int score;
    void setScore(unsigned int _s)
    {
        score = _s;
    }

public:
    Player(T _n) : name(_n), score(0) {}
    T getName() const
    {
        return name;
    }
    unsigned int getScore() const
    {
        return score;
    }
    void addScore()
    {
        setScore(getScore() + 1);
    }
    ~Player() {}
    void resetScore() { score = 0; }
};

#endif
