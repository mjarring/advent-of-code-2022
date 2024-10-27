#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "RockPaperScissors.hpp"
#include "doctest.h"
#include <string>

const std::string testFilePath = "input/day/2/test";

TEST_CASE("Test Total Score") {
  RockPaperScissors rockPaperScissors(testFilePath);
  CHECK(rockPaperScissors.getTotalScore() == 45);
}
