#include "CalorieParser.hpp"
#include "RockPaperScissors.hpp"
#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>

static const std::string CALORIES = "calories";
static const std::string ROCK_PAPER_SCISSORS = "rps";

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

  std::stringstream buffer;
  buffer << inputFile.rdbuf();

  // Determine the function
  const std::string function = argv[1];
  if (CALORIES == function) {
    CalorieParser calorieParser(buffer.str());
    std::cout << "The elf with the most calories has "
              << calorieParser.mostCalories() << " calories" << std::endl;
    std::cout << "The top three elves total " << calorieParser.topThreeTotal()
              << " calories" << std::endl;
  } else if (ROCK_PAPER_SCISSORS == function) {
    RockPaperScissors rockPaperScissors(buffer.str());
    std::cout << "Total score " << rockPaperScissors.getTotalScore()
              << std::endl;
  } else {
    std::cout << "Unknown function" << std::endl;
    return 1;
  }

  return 0;
}
