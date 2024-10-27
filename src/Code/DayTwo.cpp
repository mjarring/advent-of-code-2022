#include "RockPaperScissors.hpp"
#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

int main() {
  const std::string filePath = "input/day/2/input";
  std::ifstream inputFile(filePath);
  assert(inputFile.is_open());

  std::stringstream buffer;
  buffer << inputFile.rdbuf();
  RockPaperScissors rockPaperScissors(buffer.str());
  std::cout << "Total score " << rockPaperScissors.getTotalScore() << std::endl;
}
