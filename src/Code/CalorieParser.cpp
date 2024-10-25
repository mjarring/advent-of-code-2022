#include "CalorieParser.hpp"
#include <functional>
#include <iostream>
#include <set>
#include <sstream>
#include <string>

static std::set<int, std::greater<int>>
readCalories(const std::string &aBuffer) {
  std::set<int, std::greater<int>> elfCalories;
  int currentCalories = 0;
  std::stringstream stream(aBuffer);
  std::string line;
  while (std::getline(stream, line)) {
    if (line.empty()) {
      // We have reached the end of this elf's calorie count
      // Store the caloreis for this elf in the set
      elfCalories.insert(currentCalories);
      // Reset the calorie count for the current elf
      currentCalories = 0;
    } else {
      // Assume this is a number
      int number = stoi(line);
      // Add this number to the calorie count for current elf
      currentCalories += number;
    }
  }
  return elfCalories;
}

CalorieParser::CalorieParser(const std::string &aInput) {
  mElfCalories = readCalories(aInput);
}

void CalorieParser::solve() {
  std::set<int>::iterator itr = mElfCalories.begin();
  int most = *itr;
  std::cout << "Elf with the most calories has " << most << std::endl;
  itr++;
  int secondMost = *itr;
  itr++;
  int thirdMost = *itr;
  int topThreeTotal = most + secondMost + thirdMost;
  std::cout << "Top three Elves have " << topThreeTotal << std::endl;
}
