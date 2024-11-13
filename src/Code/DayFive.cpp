#include <cassert>
#include <deque>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

using MoveQuantity = size_t;
using MoveSource = size_t;
using MoveDestination = size_t;

static std::ifstream openFile(const std::string &aFilePath) {
  std::ifstream inputFile(aFilePath);
  assert(inputFile.is_open());
  return inputFile;
}

static size_t readNumStacks(const std::string &aFilePath) {
  std::ifstream inputFile = openFile(aFilePath);
  std::string line;
  std::getline(inputFile, line);
  inputFile.close();
  size_t length = line.length();
  int numStacks = 1;
  length--;
  while (length > 4) {
    length -= 4;
    numStacks++;
  }
  return numStacks;
}

static std::vector<std::deque<char>> readStacks(const std::string &aFilePath,
                                                const size_t aNumStacks) {
  std::vector<std::deque<char>> stacks;
  for (size_t i = 0; i < aNumStacks; i++) {
    stacks.push_back(std::deque<char>());
  }
  std::ifstream inputFile = openFile(aFilePath);
  std::string line;
  while (std::getline(inputFile, line)) {
    if (line.empty()) {
      break;
    }

    if (line.find_first_of("0123456789") != std::string::npos) {
      break;
    }

    // Start at char 1 of the line and read every 4*i character.
    // If char is a upper case letter, put it in stack i
    for (size_t stackIndex = 0; stackIndex < aNumStacks; stackIndex++) {
      size_t charIndex = 1 + stackIndex * 4; // Index into line
      assert(charIndex < line.length());
      char crate = line.at(charIndex);
      if (std::isupper(crate)) {
        // Use push_back because reading stacks top to bottom
        stacks[stackIndex].emplace_back(crate);
      }
    }
  }
  return stacks;
}

static std::tuple<MoveQuantity, MoveSource, MoveDestination>
readMoveOperation(const std::string &aLine) {
  std::stringstream ss(aLine);
  std::string word, nextWord;
  MoveQuantity quantity = 0;
  MoveSource source = 0;
  MoveDestination destination = 0;
  while (ss >> word && ss >> nextWord) {
    if (word == "move") {
      quantity = std::stoi(nextWord);
    } else if (word == "from") {
      source = std::stoi(nextWord);
    } else if (word == "to") {
      destination = std::stoi(nextWord);
    }
  }
  return std::make_tuple(quantity, source, destination);
}

class SupplyStack {
public:
  SupplyStack(const std::string &aFilePath)
      : mFilePath(aFilePath), mNumStacks(readNumStacks(aFilePath)),
        mStacks(readStacks(aFilePath, mNumStacks)) {}

  void rearrangeCrates();
  std::string getTopMessage();

private:
  void performOperation(const MoveQuantity aQuantity, const MoveSource aSource,
                        const MoveDestination aDestination);

  std::string mFilePath;
  size_t mNumStacks;
  std::vector<std::deque<char>> mStacks;
};

std::string SupplyStack::getTopMessage() {
  std::string message;
  for (const auto &stack : mStacks) {
    message += stack.front();
  }
  return message;
}

void SupplyStack::rearrangeCrates() {
  std::ifstream inputFile = openFile(mFilePath);
  std::string line;
  while (std::getline(inputFile, line)) {
    if (line.find("move") == std::string::npos) {
      continue;
    }

    if (line.empty()) {
      continue;
    }

    MoveQuantity quantity;
    MoveSource source;
    MoveDestination destination;
    std::tie(quantity, source, destination) = readMoveOperation(line);
    performOperation(quantity, source, destination);
  }
}

void SupplyStack::performOperation(const MoveQuantity aQuantity,
                                   const MoveSource aSource,
                                   const MoveDestination aDestination) {
  const size_t sourceIndex = aSource - 1;
  assert(sourceIndex >= 0);
  const size_t destinationIndex = aDestination - 1;
  assert(destinationIndex >= 0);
  for (size_t i = 0; i < aQuantity; ++i) {
    mStacks[destinationIndex].emplace_front(mStacks[sourceIndex].front());
    mStacks[sourceIndex].pop_front();
  }
}

TEST_CASE("Test Top Message") {
  SupplyStack supplyStack("input/day/5/test.txt");
  supplyStack.rearrangeCrates();
  CHECK("CMZ" == supplyStack.getTopMessage());
}

int main() {
  doctest::Context context;
  int res = context.run();
  if (context.shouldExit()) {
    return res;
  }

  const std::string filePath = "input/day/5/input.txt";
  SupplyStack supplyStack(filePath);
  supplyStack.rearrangeCrates();
  std::cout << "Message: " << supplyStack.getTopMessage() << std::endl;

  return res;
}
