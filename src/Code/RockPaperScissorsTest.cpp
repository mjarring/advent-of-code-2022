#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "RockPaperScissors.hpp"
#include "doctest.h"

const std::string input = "A Y\nB X\nC Z\n";

TEST_CASE("Test Total Score") {
  RockPaperScissors rockPaperScissors(input);
  CHECK(rockPaperScissors.totalScore() == 15);
}
