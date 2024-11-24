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

static std::string getTopMessage(const std::vector<std::deque<char>> &aStacks) {
  std::string message;
  for (const auto &stack : aStacks) {
    message += stack.front();
  }
  return message;
}

static void performOperation(std::vector<std::deque<char>> &aStacks,
                             const MoveQuantity aQuantity,
                             const MoveSource aSource,
                             const MoveDestination aDestination,
                             const bool aCrateMover9000) {
  const size_t sourceIndex = aSource - 1;
  assert(sourceIndex >= 0);
  const size_t destinationIndex = aDestination - 1;
  assert(destinationIndex >= 0);
  if (aCrateMover9000) {
    for (size_t i = 0; i < aQuantity; ++i) {
      aStacks[destinationIndex].emplace_front(aStacks[sourceIndex].front());
      aStacks[sourceIndex].pop_front();
    }
  } else {
    std::deque<char> craneStack;
    for (size_t i = 0; i < aQuantity; ++i) {
      craneStack.emplace_back(aStacks[sourceIndex].front());
      aStacks[sourceIndex].pop_front();
    }
    for (size_t i = 0; i < aQuantity; ++i) {
      aStacks[destinationIndex].emplace_front(craneStack.back());
      craneStack.pop_back();
    }
  }
}

static void rearrangeCrates(const std::string &aFilePath,
                            std::vector<std::deque<char>> &aStacks,
                            const bool aCrateMover9000) {
  std::ifstream inputFile = openFile(aFilePath);
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
    performOperation(aStacks, quantity, source, destination, aCrateMover9000);
  }
}

TEST_CASE("Test Top Message") {
  const std::string filePath = "input/day/5/test.txt";
  size_t numStacks = readNumStacks(filePath);
  std::vector<std::deque<char>> stacks = readStacks(filePath, numStacks);
  rearrangeCrates(filePath, stacks, true);
  CHECK("CMZ" == getTopMessage(stacks));
}

TEST_CASE("Test Top Message 2") {
  const std::string filePath = "input/day/5/test.txt";
  size_t numStacks = readNumStacks(filePath);
  std::vector<std::deque<char>> stacks = readStacks(filePath, numStacks);
  rearrangeCrates(filePath, stacks, false);
  CHECK("MCD" == getTopMessage(stacks));
}

int main() {
  doctest::Context context;
  int res = context.run();
  if (context.shouldExit()) {
    return res;
  }

  const std::string filePath = "input/day/5/input.txt";
  size_t numStacks = readNumStacks(filePath);
  std::vector<std::deque<char>> stacks = readStacks(filePath, numStacks);
  rearrangeCrates(filePath, stacks, true);
  std::cout << "Crate Mover 9000: " << getTopMessage(stacks) << std::endl;

  std::vector<std::deque<char>> secondStacks = readStacks(filePath, numStacks);
  rearrangeCrates(filePath, secondStacks, false);
  std::cout << "Crate Mover 9001: " << getTopMessage(secondStacks) << std::endl;
  return res;
}
