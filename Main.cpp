#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <iostream>

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

    // pasalinamas platusis bruksnelis kuris buna lietuviskuose textuose
    else if (word == "–")
        return false;

    else
        for (auto &w : word)
            if (ispunct(w) || isdigit(w)) // tikrinama ar zodzio simbolis yra raide, jeigu ne, simbolis istrinamas
                word.erase(std::remove(word.begin(), word.end(), w), word.end());

    return true;
}

// funkcija, gaunanti tikraji ilgi (kad outputas buut grazesnis)
inline size_t get_length(const std::string &str)
{
    return (str.length() - std::count_if(str.begin(), str.end(), [](char c) -> bool { return (c & 0xC0) == 0x80; }));
}

void file_output(std::map<std::string, std::pair<int, std::vector<int>>> map_of_words, std::string filename)
{
    std::ofstream file(filename);

    file << std::left << std::setw(20) << "Žodis" << std::setw(20) << "Pasikartoja"
         << "Eilutėse" << std::endl
         << std::string(80, '-') << std::endl;

    for (auto &m : map_of_words)
    {
        if (m.second.first > 1)
        {
            size_t additional = m.first.size() - get_length(m.first);
            file << std::left << std::setw(20 + additional) << m.first << std::setw(9) << m.second.first << std::right << std::setw(12);
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
    std::ifstream file(filename);
    std::string line = " ", word = " ";

    int line_count = 0;

    while (std::getline(file, line))
    {
        ++line_count;
        std::istringstream iss(line);

        // zodziu nuskaitymas i map'a
        while (iss >> word)
        {
            if (!only_word(word))
                continue;
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
    std::map<std::string, std::pair<int, std::vector<int>>> map_of_words = read_from_file("text.txt");
    file_output(map_of_words, "result.txt");

    return 0;
}