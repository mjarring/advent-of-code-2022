#include "CalorieParser.hpp"
#include <cassert>
#include <fstream>
#include <sstream>
#include <string>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

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
