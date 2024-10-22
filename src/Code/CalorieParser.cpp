#include "CalorieParser.hpp"
#include <fstream>
#include <functional>
#include <set>
#include <string>

using namespace std;

set<int, greater<int>> CalorieParser::parseCalories(ifstream &aFile) {
  set<int, greater<int>> elfCalories;
  int currentCalories = 0;
  string line;
  while (getline(aFile, line)) {
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
