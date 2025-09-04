#include "gameboard.h"
#include <QDir>
#include <QFileInfoList>

Str Gameboard::getWhereObraski() const
{
    return where_obraski;
}

unsigned int Gameboard::getNumberOfPairs() const
{
    return number_of_pairs;
}

std::vector<Str> read_folder(const Str &fold)
{
    std::vector<Str> result;

    QDir dir(fold);
    if (!dir.exists()) {
        throw std::runtime_error(("Složka neexistuje: " + fold).toStdString());
    }

    QFileInfoList files = dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot);

    for (const QFileInfo &fileInfo : files) {
        result.push_back(fileInfo.absoluteFilePath());
    }

    return result;
}

Gameboard::~Gameboard()
{
}

const vector_of_cards &Gameboard::getDeck() const
{
    return dEck;
}

vector_of_cards &Gameboard::getDeck()
{
    return dEck;
}

void Gameboard::showInvisibleCards() const
{
    const auto &deck = getDeck();

    for (size_t i = 0; i < deck.size(); i++)
    {
        if (!deck[i].isVisible())
        {
            std::cout << "Index: "
                      << i
                      //<< " karta: "
                      //<< deck[i].getId()
                      << " je viditelny? "
                      << deck[i].isVisible() << "\n";
        }
    }
    std::cout << "hotovo\n";
}
std::vector<QString> read_folder(const std::string &fold)
{
    auto actual_path = std::filesystem::current_path() / fold;
    std::vector<QString> result;
    try
    {
        for (const auto &entry : fs::directory_iterator(actual_path))
        {
            result.push_back(QString::fromStdString(entry.path().string()));
        }
    }
    catch (const fs::filesystem_error &e)
    {
        std::cerr << "Chyba: " << e.what() << "\n";
    }

    return result;
}
