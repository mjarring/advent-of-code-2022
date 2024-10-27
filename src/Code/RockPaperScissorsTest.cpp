#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "RockPaperScissors.hpp"
#include "doctest.h"
#include <cassert>
#include <fstream>
#include <sstream>
#include <string>

const std::string testFilePath = "input/day/2/test";

std::string openTestFile(const std::string &aPath) {
  std::ifstream inputFile(aPath);
  assert(inputFile.is_open());

  std::stringstream buffer;
  buffer << inputFile.rdbuf();
  return buffer.str();
}

TEST_CASE("Test Total Score") {
  const std::string input = openTestFile(testFilePath);
  RockPaperScissors rockPaperScissors(input);
  CHECK(rockPaperScissors.getTotalScore() == 15);
}
