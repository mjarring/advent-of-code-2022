#include "CalorieParser.hpp"
#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

int main() {
  const std::string filePath = "input/day/1/input";
  std::ifstream inputFile(filePath);
  assert(inputFile.is_open());

  std::stringstream buffer;
  buffer << inputFile.rdbuf();
  CalorieParser calorieParser(buffer.str());
  std::cout << "The elf with the most calories has "
            << calorieParser.mostCalories() << " calories" << std::endl;
  std::cout << "The top three elves total " << calorieParser.topThreeTotal()
            << " calories" << std::endl;
}
