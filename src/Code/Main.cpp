#include "CalorieParser.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

static const std::string CALORIES = "calories";

int main(int argc, char **argv) {
  // Validate arguments
  if (argc != 3) {
    std::cout << "Usage: ./advent function input" << std::endl;
    return 1;
  }

  // Open the file
  const std::string filePath = argv[2];
  std::ifstream inputFile(filePath);
  if (!inputFile.is_open()) {
    std::cout << "Cannot open file " << filePath << std::endl;
    return 1;
  }

  // Determine the function
  const std::string function = argv[1];
  if (CALORIES == function) {
    std::stringstream buffer;
    buffer << inputFile.rdbuf();
    CalorieParser calorieParser(buffer.str());
    std::cout << "The elf with the most calories has "
              << calorieParser.mostCalories() << " calories" << std::endl;
    std::cout << "The top three elves total " << calorieParser.topThreeTotal()
              << " calories" << std::endl;
  }

  return 0;
}
