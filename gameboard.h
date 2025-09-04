#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include <vector>
#include <iostream>
#include <string>
#include <random>
#include <filesystem>
#include <stdexcept>
#include <algorithm>
#include "Card.h"
#include <QString>
#include <ostream>
//typedef std::string Str; // konzolova verze
typedef QString Str; //qt verze xd
typedef std::vector<Str> vector_of_pics_names;
typedef std::vector<Card<Str>> vector_of_cards;
namespace fs = std::filesystem;

std::vector<Str> read_folder(const Str &fold);

inline std::ostream& operator<<(std::ostream& os, const QString& str)
{
    return os << str.toStdString();
}

class Gameboard
{
private:
    Str where_obraski;
    unsigned int number_of_pairs;
    vector_of_cards dEck;

public:
    Str getWhereObraski() const;
    unsigned int getNumberOfPairs() const;
    Gameboard(const Str &_wo, unsigned int _nop);
    ~Gameboard();
    const vector_of_cards& getDeck() const;
    vector_of_cards& getDeck();
    friend std::ostream &operator<<(std::ostream &os, const Gameboard &gb)
    {
        for (const auto &card : gb.getDeck())
        {
            os << "ID: " << card.getId()
            << ", obrazek: " << card.getPicca()
            << ", viditelny: " << (card.isVisible() ? "ano" : "ne") << '\n';
        }
        return os;
    }
    void showInvisibleCards() const;

};
#endif
