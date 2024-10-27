#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "RucksackReorganizer.hpp"
#include "doctest.h"
#include <string>

const std::string testFilePath = "input/day/3/test.txt";

TEST_CASE("Test Total Priority") {
  RucksackReorganizer reorganizer(testFilePath);
  CHECK(157 == reorganizer.getTotalPriority());
}
