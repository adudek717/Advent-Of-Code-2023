#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>

int main()
{
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
    int sum = 0;
    while (std::getline(inputFile, line)) {
        for (int i = 0; i < line.size(); i++) {
            if (isdigit(line.at(i))) {
                if (firstNum == -1) {
                    firstNum = line.at(i) - '0';
                }
                secondNum = line.at(i) - '0';
            }
        }
        sum += 10 * firstNum + secondNum;
        firstNum = -1;
        secondNum = -1;
    }
    std::cout << "Sum: " << sum << std::endl;
    inputFile.close();
}