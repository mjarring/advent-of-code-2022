#include "CalorieParser.hpp"
#include <set>
#include <sstream>
#include <string>

CalorieParser::CalorieParser(const std::string &aInput) {
  int currentCalories = 0;
  std::stringstream stream(aInput);
  std::string line;
  while (std::getline(stream, line) || currentCalories > 0) {
    if (line.empty()) {
      // We have reached the end of this elf's calorie count
      // Store the caloreis for this elf in the set
      mElfCalories.insert(currentCalories);
      // Reset the calorie count for the current elf
      currentCalories = 0;
    } else {
      // Assume this is a number
      int number = stoi(line);
      // Add this number to the calorie count for current elf
      currentCalories += number;
    }
  }
}

int CalorieParser::mostCalories() {
  std::set<int>::iterator itr = mElfCalories.begin();
  int most = *itr;
  return most;
}

int CalorieParser::topThreeTotal() {
  std::set<int>::iterator itr = mElfCalories.begin();
  int most = *itr;
  itr++;
  int secondMost = *itr;
  itr++;
  int thirdMost = *itr;
  int topThreeTotal = most + secondMost + thirdMost;
  return topThreeTotal;
}
