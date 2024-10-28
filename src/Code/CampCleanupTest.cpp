#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "CampCleanup.hpp"
#include "doctest.h"
#include <string>

const std::string testFilePath = "input/day/4/test.txt";

TEST_CASE("Test Overlapping Assignments") {
  CampCleanup cleanup(testFilePath);
  CHECK(2 == cleanup.getContainedAssignments());
}
