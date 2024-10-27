#include "RucksackReorganizer.hpp"
#include <cassert>
#include <cctype>
#include <fstream>
#include <vector>

// 64 is ASCII value of 'A', 27 is the priority of 'A' rucksack item
const int ASCII_UPPER_CASE_OFFSET = 38;
// 97 is ASCII value of 'a', 1 is the priority of 'a' rucksack item
const int ASCII_LOWER_CASE_OFFSET = 96;

int getItemPriority(const char aItem) {
  assert(isupper(aItem) || islower(aItem));
  if (isupper(aItem)) {
    return aItem - ASCII_UPPER_CASE_OFFSET;
  } else {
    return aItem - ASCII_LOWER_CASE_OFFSET;
  }
}

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
  return getItemPriority(incorrectItem);
}

int calculateBadgePriority(std::vector<std::string> &aGroup) {
  size_t badgePos = aGroup[0].find_first_of(aGroup[1]);
  char badge = aGroup[0].at(badgePos);
  while (aGroup[2].find_first_of(badge) == std::string::npos) {
    // Remove badge from group 0 and search group 0 again
    aGroup[0].erase(badgePos, 1);
    badgePos = aGroup[0].find_first_of(aGroup[1]);
    badge = aGroup[0].at(badgePos);
  }
  return getItemPriority(badge);
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

int RucksackReorganizer::getBadgePriority() {
  std::vector<std::string> group;
  std::ifstream inputFile(mInputFilePath);
  assert(inputFile.is_open());
  std::string line = "";
  int totalBadgePriority = 0;
  while (std::getline(inputFile, line)) {
    group.push_back(line);
    if (group.size() == 3) {
      totalBadgePriority += calculateBadgePriority(group);
      group.clear();
    }
  }
  return totalBadgePriority;
}
