#include "RucksackReorganizer.hpp"
#include <cassert>
#include <fstream>

RucksackReorganizer::RucksackReorganizer(const std::string &aFilePath)
    : mTotalPriority(0) {
  std::string line = "";
  std::ifstream inputFile(aFilePath);
  assert(inputFile.is_open());
  while (std::getline(inputFile, line)) {
    mTotalPriority++;
  }
}

int RucksackReorganizer::getTotalPriority() { return mTotalPriority; }
