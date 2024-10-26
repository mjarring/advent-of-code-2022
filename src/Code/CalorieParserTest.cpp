#include "CalorieParser.hpp"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

const std::string input =
    "1000\n2000\n3000\n\n4000\n\n5000\n6000\n\n7000\n8000\n9000\n\n10000\n";

TEST_CASE("Testing readCalories") {
  CalorieParser calorieParser(input);
  CHECK(calorieParser.mostCalories() == 24000);
}

TEST_CASE("Test topThreeTotal") {
  CalorieParser calorieParser(input);
  CHECK(calorieParser.topThreeTotal() == 45000);
}
