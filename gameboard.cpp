#include "gameboard.h"


Str Gameboard::getWhereObraski() const
{
    return where_obraski;
}

unsigned int Gameboard::getNumberOfPairs() const
{
    return number_of_pairs;
}

Gameboard::Gameboard(const Str &_wo, unsigned int _nop)
    : where_obraski(_wo), number_of_pairs(_nop)
{
    // 1) načti cesty k obrázkům (funguje i pro QRC ":/pic")
    auto files = read_folder(where_obraski);                              // :contentReference[oaicite:0]{index=0}
    if (files.empty())
        throw std::runtime_error(("Ve složce nejsou žádné obrázky: " + where_obraski).toStdString());

    // 2) vezmi jen tolik párů, kolik reálně je obrázků
    number_of_pairs = std::min<unsigned int>(number_of_pairs, files.size());

    // 3) zamíchej seznam obrázků a usekni na N
    std::shuffle(files.begin(), files.end(), std::mt19937{std::random_device{}()});
    files.resize(number_of_pairs);

    // 4) z každého udělej dvojici karet se stejným id
    dEck.clear();
    dEck.reserve(number_of_pairs * 2);
    for (unsigned int i = 0; i < number_of_pairs; ++i) {
        dEck.emplace_back(i, files[i]);                                   // Card<Str>(id, path) :contentReference[oaicite:1]{index=1}
        dEck.emplace_back(i, files[i]);
    }

    // 5) finální promíchání balíčku
    std::shuffle(dEck.begin(), dEck.end(), std::mt19937{std::random_device{}()});
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
