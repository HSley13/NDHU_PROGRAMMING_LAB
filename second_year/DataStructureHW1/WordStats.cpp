#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

class TextProcessor {
  public:
    TextProcessor(const std::string &inputFilePath) {
        inputFile.open(inputFilePath);

        if (!inputFile) {
            throw std::runtime_error("Error opening input file!");
        }

        wordCountFile.open("DataStructureHW1/word_histogram.txt");
        charCountFile.open("DataStructureHW1/char_statistics.txt");

        if (!wordCountFile || !charCountFile) {
            throw std::runtime_error("Error opening output files!");
        }
    }

    ~TextProcessor() {
        inputFile.close();
        wordCountFile.close();
        charCountFile.close();
    }

    void process() {
        while (std::getline(inputFile, line)) {
            line = processString(line);
            std::istringstream stream{line};

            while (stream >> word) {
                wordCountMap[word]++;
                for (const char &ch : word) {
                    charCountMap[ch]++;
                }
            }
        }

        writeWordCounts(wordCountMap);
        writeCharCounts(charCountMap);
    }

  private:
    std::ifstream inputFile;
    std::ofstream wordCountFile;
    std::ofstream charCountFile;

    std::string line, word;
    std::map<std::string, int> wordCountMap;
    std::map<char, int> charCountMap;

    std::string processString(std::string &str) {
        str.erase(std::remove_if(str.begin(), str.end(), [](unsigned char c) {
                      return !std::isalpha(c) && !std::isspace(c);
                  }),
                  str.end());

        std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c) {
            return std::tolower(c);
        });

        return str;
    }

    void writeWordCounts(const std::map<std::string, int> &wordCountMap) {
        for (const std::pair<std::string, int> &entry : wordCountMap) {
            wordCountFile << entry.first << " : " << entry.second << "\n";
        }
    }

    void writeCharCounts(const std::map<char, int> &charCountMap) {
        std::vector<std::pair<char, int>> charVector(charCountMap.begin(), charCountMap.end());
        std::sort(charVector.begin(), charVector.end(), [](const std::pair<char, int> &a, const std::pair<char, int> &b) {
            return a.second < b.second;
        });

        for (const std::pair<char, int> &entry : charVector) {
            charCountFile << entry.first << " : " << entry.second << "\n";
        }
    }
};

int main(void) {
    try {
        TextProcessor processor("DataStructureHW1/example.txt");
        processor.process();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}
