#include "CampCleanup.hpp"
#include <iostream>
#include <string>

int main() {
  const std::string filePath = "input/day/4/input.txt";
  CampCleanup campCleanup(filePath);
  std::cout << "Contained assignments: "
            << campCleanup.getContainedAssignments() << std::endl;
  std::cout << "Overlapping assignments: " << campCleanup.getOverlappingRanges()
            << std::endl;
}
