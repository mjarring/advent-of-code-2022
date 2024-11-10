#include <cassert>
#include <fstream>
#include <functional>
#include <iostream>
#include <set>
#include <sstream>
#include <string>

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

class CalorieParser {
public:
  CalorieParser(const std::string &aInput);
  int mostCalories();
  int topThreeTotal();

private:
  std::set<int, std::greater<int>> mElfCalories;
};

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

const std::string testFilePath = "input/day/1/test";

std::string openTestFile(const std::string &aPath) {
  std::ifstream inputFile(aPath);
  assert(inputFile.is_open());

  std::stringstream buffer;
  buffer << inputFile.rdbuf();
  return buffer.str();
}

TEST_CASE("Testing mostCalories") {
  const std::string input = openTestFile(testFilePath);
  CalorieParser calorieParser(input);
  CHECK(calorieParser.mostCalories() == 24000);
}

TEST_CASE("Test topThreeTotal") {
  const std::string input = openTestFile(testFilePath);
  CalorieParser calorieParser(input);
  CHECK(calorieParser.topThreeTotal() == 45000);
}

int main() {
  // Set up doctest and run test cases first
  doctest::Context context;
  int res = context.run();
  if (context.shouldExit()) {
    return res;
  }

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

  return res;
}
