#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>

struct Combination {
    int red = 0;
    int green = 0;
    int blue = 0;
};

struct Game {
    int id = 0;
    std::vector<Combination> combinations;
};

int main() {
    std::filesystem::path filePath = "lines.txt";
    if (!std::filesystem::exists(filePath)) {
        std::cerr << "File \"" << filePath << "\" not found..." << std::endl;
        return -1;
    }

    std::ifstream inputFile(filePath);
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open the \"" << filePath << "\" file..." << std::endl;
        return -1;
    }

    Game requirement{0, {{12, 13, 14}}};

    std::string line;
    std::vector<Game> games;
    while (std::getline(inputFile, line)) {
        std::string word;
        bool wordIsNum = false;
        int lastNum = 0;
        Game newGame;
        Combination newCombination;
        
        for(int i = 0; i < line.size(); ++i) {
            // mark word as a colors number
            if (isdigit(line.at(i))) { wordIsNum = true; }
            
            // save game id
            if (line.at(i) == ':') {
                newGame.id = stoi(word);
                word.clear();
                wordIsNum = false;
                continue;
            }

            if (line.at(i) == ' ') {
                if (wordIsNum) {
                    lastNum = stoi(word);
                    word.clear();
                    wordIsNum = false;
                    continue;
                } else {
                    word.clear();
                    continue;
                }
            }

            if (i == line.size() - 1) {
                word += line.at(i);
            }

            // determine color, reset word, reset wordIsNum
            if (line.at(i) == ',' || line.at(i) == ';' || i == line.size() - 1) {
                if (word == "red") {
                    newCombination.red = lastNum;
                    lastNum = 0;
                } else if (word == "blue") {
                    newCombination.blue = lastNum;
                    lastNum = 0;
                } else if (word == "green") {
                    newCombination.green = lastNum;
                    lastNum = 0;
                }
                if (line.at(i) == ';') {
                    newGame.combinations.push_back(newCombination);
                    newCombination = Combination{0};
                }
                if (i == line.size() - 1) {
                    newGame.combinations.push_back(newCombination);
                    newCombination = Combination{0};
                    games.push_back(newGame);
                    newGame = Game{0};
                }
            }
            word += line.at(i);
        }

        int winningGamesSum = 0;
        for (const auto& g : games) {

            std::cout << "Game: " << g.id << std::endl;
            std::cout << "Combinations: " << g.combinations.size() << std::endl;
            for (int i = 0; i < g.combinations.size(); ++i) {
                std::cout << i + 1 << " - "
                          << "R: " << g.combinations.at(i).red << " "
                          << "G: " << g.combinations.at(i).green << " "
                          << "B: " << g.combinations.at(i).blue << " "
                          << std::endl;
            }

            int largestR = INT32_MIN;
            int largestG = INT32_MIN;
            int largestB = INT32_MIN;
            for (const auto& c : g.combinations) {
                if (c.red != 0)
                    largestR = std::max(largestR, c.red);
                if (c.green != 0)    
                    largestG = std::max(largestG, c.green);
                if (c.blue != 0)    
                    largestB = std::max(largestB, c.blue);
            }
            if (largestR == INT32_MIN) largestR = 1;
            if (largestG == INT32_MIN) largestG = 1;
            if (largestB == INT32_MIN) largestB = 1;
            std::cout << "Current game power: " << (largestR * largestG * largestB) << std::endl;
            winningGamesSum += (largestR * largestG * largestB);
        }

        std::cout << "Winning games power: " << winningGamesSum << std::endl;
    }
    inputFile.close();
}