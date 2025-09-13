#include "gameboard.h"


Str Gameboard::getWhereObraski() const
{
    return where_obraski;
}

unsigned int Gameboard::getNumberOfPairs() const
{
    return number_of_pairs;
}


// qt verze
Gameboard::Gameboard(const QStringList &_wo, unsigned int _nop)
    : where_obraski(""), number_of_pairs(_nop)
{
    // místo read_folder() seznam z .qrc
    std::vector<Str> files;
    for (const auto &p : _wo) {
        files.push_back(p);
    }

    if (files.empty())
        throw std::runtime_error("Žádné obrázky k dispozici!");

    number_of_pairs = std::min<unsigned int>(number_of_pairs, files.size());


    dEck.clear();
    dEck.reserve(number_of_pairs * 2);
    for (unsigned int i = 0; i < number_of_pairs; ++i) {
        dEck.emplace_back(i, files[i]);
        dEck.emplace_back(i, files[i]);
    }

    // shuffle decku
    static std::random_device rd;
    static std::mt19937 g(rd());

    std::shuffle(dEck.begin(), dEck.end(), g);
}


// Původní verze
Gameboard::Gameboard(const Str &_wo, unsigned int _nop)
    : where_obraski(_wo), number_of_pairs(_nop)
{

    auto files = read_folder(where_obraski);
    if (files.empty())
        throw std::runtime_error(("Ve složce nejsou žádné obrázky: " + where_obraski).toStdString());

    number_of_pairs = std::min<unsigned int>(number_of_pairs, files.size());


    std::shuffle(files.begin(), files.end(), std::mt19937{std::random_device{}()});
    files.resize(number_of_pairs);


    dEck.clear();
    dEck.reserve(number_of_pairs * 2);
    for (unsigned int i = 0; i < number_of_pairs; ++i) {
        dEck.emplace_back(i, files[i]);
        dEck.emplace_back(i, files[i]);
    }

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
