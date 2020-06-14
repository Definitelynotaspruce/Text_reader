#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <locale>
#include <iomanip>

// tikrinimas ar stringas yra url
bool url_check(std::string word)
{
    std::vector<std::string> url = {"http", "www."};
    for (auto u : url)
        if (word.substr(0, 4) == u)
            return true;
    return false;
}

// is nuskaitytu zodziu pasaliname simbolius
bool only_word(std::string &word)
{
    if (url_check(word))
        return true;
    else
    {
        for (auto &w : word)
        {
            if (!isalpha(w)) // tikrinama ar zodzio simbolis yra raide, jeigu ne, simbolis istrinamas
            {
                word.erase(std::remove(word.begin(), word.end(), w), word.end());
            }
        }
    }
    return true;
}

void file_output(std::map<std::string, std::pair<int, std::vector<int>>> map_of_words, std::string filename)
{
    std::ofstream file;
    file.open(filename);

    for (auto &m : map_of_words)
    {
        if (m.second.first > 1)
        {
            file << std::setw(15) << std::left << m.first
                 << std::setw(30) << std::right << m.second.first << "  ";
            for (auto &w : m.second.second)
                file << w << " ";
            file << std::endl;
        }
    }
    file << "Linkai:" << std::endl;
    for (auto &m : map_of_words)
    {
        if (m.first.substr(0, 4) == "http" || m.first.substr(0, 4) == "www.")
            file << m.first << std::endl;
    }
    file.close();
}

std::map<std::string, std::pair<int, std::vector<int>>> read_from_file(std::string filename)
{
    std::map<std::string, std::pair<int, std::vector<int>>> map_of_words;
    std::ifstream file;
    std::string line = " ", word = " ";
    file.open(filename);
    int line_count = 0;

    while (std::getline(file, line))
    {
        ++line_count;
        std::istringstream iss(line);

        while (iss >> word && only_word(word))
        {
            if (!word.size())
                continue;
            if (map_of_words.find(word) == map_of_words.end())
            {
                map_of_words[word].first = 1;
                map_of_words[word].second = std::vector<int>{line_count};
            }
            else
            {
                ++map_of_words[word].first;
                map_of_words[word].second.push_back(line_count);
            }
        }
    }

    file.close();
    return map_of_words;
}

int main()
{
    std::map<std::string, std::pair<int, std::vector<int>>> map_of_words = read_from_file("text3.txt");
    file_output(map_of_words, "result.txt");

    return 0;
}