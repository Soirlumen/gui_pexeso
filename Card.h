#ifndef CARD_H
#define CARD_H

template <typename T>
class Card
{
private:
    unsigned int id;
    T picca;
    bool visible;

public:
    Card(unsigned int _id, T _picca) : id(_id), picca(_picca), visible(false) {}
    T getPicca() const
    {
        return picca;
    }
    bool isVisible() const
    {
        return visible;
    }
    void flipCard()
    {
        visible = !visible;
    }
    unsigned int getId() const
    {
        return id;
    }
    ~Card() {}
};

#endif
