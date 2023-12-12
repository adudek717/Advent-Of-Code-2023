#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <unordered_map>

std::unordered_map<std::string, int> numbersMap {
    {"one", 1},
    {"two", 2},
    {"three", 3},
    {"four", 4},
    {"five", 5},
    {"six", 6},
    {"seven", 7},
    {"eight", 8},
    {"nine", 9}
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

    std::string line;

    int firstNum = -1;
    int secondNum = -1;
    int firstIdx = INT32_MAX;
    int secondIdx = -1;
    int sum = 0;
    while (std::getline(inputFile, line)) {
        for (const auto& [key, value] : numbersMap) {
            auto foundFirst = static_cast<int>(line.find(key));
            if (foundFirst != std::string::npos) {
                if (static_cast<int>(foundFirst) < firstIdx) {
                    firstNum = value;
                    firstIdx = foundFirst;
                }
            }

            auto foundSecond = static_cast<int>(line.rfind(key));
            if (foundSecond != std::string::npos) {
                if (foundSecond > secondIdx) {
                    secondNum = value;
                    secondIdx = foundSecond;
                }
            }
        }
        
        for (int i = 0; i < line.size(); i++) {
            if (isdigit(line.at(i))) {
                if (i <= firstIdx) {
                    firstNum = line.at(i) - '0';
                    firstIdx = i;
                }
                if (i >= secondIdx) {
                    secondNum = line.at(i) - '0';
                }
            }
        }
        sum += 10 * firstNum + secondNum;
        std::cout << firstNum << " " << secondNum << std::endl;
        firstNum = -1;
        secondNum = -1;
        firstIdx = INT32_MAX;
        secondIdx = -1;
    }
    std::cout << "Sum: " << sum << std::endl;
    inputFile.close();
}