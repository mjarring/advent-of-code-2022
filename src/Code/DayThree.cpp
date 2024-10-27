#include "RucksackReorganizer.hpp"
#include <iostream>
#include <string>

int main() {
  const std::string filePath = "input/day/3/input.txt";
  RucksackReorganizer reorganizer(filePath);
  std::cout << "Sum of priorities: " << reorganizer.getTotalPriority()
            << std::endl;
}
