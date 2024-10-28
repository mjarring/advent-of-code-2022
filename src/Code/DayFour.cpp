#include "CampCleanup.hpp"
#include <iostream>
#include <string>

int main() {
  const std::string filePath = "input/day/4/input.txt";
  CampCleanup campCleanup(filePath);
  std::cout << "Overlapping assignments: "
            << campCleanup.getContainedAssignments() << std::endl;
}
