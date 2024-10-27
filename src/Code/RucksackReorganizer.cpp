#include "RucksackReorganizer.hpp"
#include <cassert>
#include <cctype>
#include <fstream>

// 64 is ASCII value of 'A', 27 is the priority of 'A' rucksack item
const int ASCII_UPPER_CASE_OFFSET = 38;
// 97 is ASCII value of 'a', 1 is the priority of 'a' rucksack item
const int ASCII_LOWER_CASE_OFFSET = 96;

char findIncorrectItem(const std::string &aRucksack) {
  const size_t totalLength = aRucksack.length();
  const size_t halfLength = totalLength / 2;
  const std::string firstCompartment = aRucksack.substr(0, halfLength);
  const std::string secondCompartment =
      aRucksack.substr(halfLength, totalLength);
  const size_t incorrectItemPos =
      secondCompartment.find_first_of(firstCompartment);
  assert(incorrectItemPos != std::string::npos);
  return secondCompartment.at(incorrectItemPos);
}

int calculatePriority(const std::string &aRucksack) {
  const char incorrectItem = findIncorrectItem(aRucksack);
  assert(isupper(incorrectItem) || islower(incorrectItem));
  int priority = 0;
  if (isupper(incorrectItem)) {
    int itemValue = incorrectItem;
    priority = itemValue - ASCII_UPPER_CASE_OFFSET;
  } else {
    int itemValue = incorrectItem;
    priority = itemValue - ASCII_LOWER_CASE_OFFSET;
  }
  return priority;
}

RucksackReorganizer::RucksackReorganizer(const std::string &aFilePath)
    : mInputFilePath(aFilePath) {}

int RucksackReorganizer::getTotalPriority() {
  std::string line = "";
  std::ifstream inputFile(mInputFilePath);
  assert(inputFile.is_open());
  int totalPriority = 0;
  while (std::getline(inputFile, line)) {
    totalPriority += calculatePriority(line);
  }
  return totalPriority;
}

int RucksackReorganizer::getBadgePriority() { return 1; }
