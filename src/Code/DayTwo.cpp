#include "RockPaperScissors.hpp"
#include <iostream>
#include <string>

int main() {
  const std::string filePath = "input/day/2/input.txt";
  RockPaperScissors rockPaperScissors(filePath);
  std::cout << "Total score " << rockPaperScissors.getTotalScore() << std::endl;
}
