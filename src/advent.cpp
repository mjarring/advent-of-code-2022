#include <cassert>
#include <cctype>
#include <deque>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

class CalorieParser {
public:
  CalorieParser(const std::string &aInput);
  int mostCalories();
  int topThreeTotal();

private:
  std::set<int, std::greater<int>> mElfCalories;
};

CalorieParser::CalorieParser(const std::string &aInput) {
  int currentCalories = 0;
  std::stringstream stream(aInput);
  std::string line;
  while (std::getline(stream, line) || currentCalories > 0) {
    if (line.empty()) {
      // We have reached the end of this elf's calorie count
      // Store the caloreis for this elf in the set
      mElfCalories.insert(currentCalories);
      // Reset the calorie count for the current elf
      currentCalories = 0;
    } else {
      // Assume this is a number
      int number = stoi(line);
      // Add this number to the calorie count for current elf
      currentCalories += number;
    }
  }
}

int CalorieParser::mostCalories() {
  std::set<int>::iterator itr = mElfCalories.begin();
  int most = *itr;
  return most;
}

int CalorieParser::topThreeTotal() {
  std::set<int>::iterator itr = mElfCalories.begin();
  int most = *itr;
  itr++;
  int secondMost = *itr;
  itr++;
  int thirdMost = *itr;
  int topThreeTotal = most + secondMost + thirdMost;
  return topThreeTotal;
}

std::string openTestFile(const std::string &aPath) {
  std::ifstream inputFile(aPath);
  assert(inputFile.is_open());

  std::stringstream buffer;
  buffer << inputFile.rdbuf();
  return buffer.str();
}

class RockPaperScissors {
public:
  RockPaperScissors(const std::string &aFilePath);
  unsigned int getTotalScore();

private:
  unsigned int mTotalScore;
};

enum GameToken {
  Rock,
  Paper,
  Scissors,
};

enum DesiredOutcome { Win, Loss, Draw };

const std::map<std::string, GameToken> opponentEncoding{
    {"A", GameToken::Rock},
    {"B", GameToken::Paper},
    {"C", GameToken::Scissors}};

const std::map<std::string, DesiredOutcome> outcomeEncoding{
    {"X", DesiredOutcome::Loss},
    {"Y", DesiredOutcome::Draw},
    {"Z", DesiredOutcome::Win}};

GameToken opponentStringToToken(const std::string &aString) {
  auto itr = opponentEncoding.find(aString);
  assert(itr != opponentEncoding.end());
  return itr->second;
}

DesiredOutcome parseOutcomeString(const std::string &aString) {
  auto itr = outcomeEncoding.find(aString);
  assert(itr != outcomeEncoding.end());
  return itr->second;
}

GameToken determinePlayerToken(const DesiredOutcome &aOutcome,
                               const GameToken &aOpponentToken) {
  if (aOutcome == DesiredOutcome::Draw) {
    return aOpponentToken;
  } else if (aOutcome == DesiredOutcome::Loss) {
    if (aOpponentToken == GameToken::Rock) {
      return GameToken::Scissors;
    } else if (aOpponentToken == GameToken::Paper) {
      return GameToken::Rock;
    } else {
      // Opponent played Scissors
      return GameToken::Paper;
    }
  } else {
    if (aOpponentToken == GameToken::Rock) {
      return GameToken::Paper;
    } else if (aOpponentToken == GameToken::Paper) {
      return GameToken::Scissors;
    } else {
      // Opponent played Scissors
      return GameToken::Rock;
    }
  }
}

// Score the player's selected token
int scoreToken(const GameToken &aToken) {
  switch (aToken) {
  case GameToken::Rock:
    return 1;
  case GameToken::Paper:
    return 2;
  case GameToken::Scissors:
    return 3;
  }
}

// Score the outcome of a game (win or loss for the player)
int scoreOutcome(const DesiredOutcome &aOutcome) {
  switch (aOutcome) {
  case DesiredOutcome::Loss:
    return 0;
  case DesiredOutcome::Draw:
    return 3;
  case DesiredOutcome::Win:
    return 6;
  }
}

// Calculate the score for a round. The score for a round is the score of the
// player's selected token added with the outcome of the game.
int scoreRound(const GameToken &aPlayerToken, const DesiredOutcome &aOutcome) {
  return scoreToken(aPlayerToken) + scoreOutcome(aOutcome);
}

// Parse the input game by game
RockPaperScissors::RockPaperScissors(const std::string &aFilePath)
    : mTotalScore(0) {
  std::string line = "";
  std::string delimiter = " ";
  std::ifstream inputFile(aFilePath);
  assert(inputFile.is_open());
  while (std::getline(inputFile, line)) {
    size_t pos = line.find(delimiter);
    GameToken opponentToken = opponentStringToToken(line.substr(0, pos));
    line.erase(0, pos + delimiter.length());
    DesiredOutcome outcome = parseOutcomeString(line);
    GameToken playerToken = determinePlayerToken(outcome, opponentToken);
    mTotalScore += scoreRound(playerToken, outcome);
  }
}

unsigned int RockPaperScissors::getTotalScore() { return mTotalScore; }

class RucksackReorganizer {
public:
  RucksackReorganizer(const std::string &aFilePath);
  int getTotalPriority();
  int getBadgePriority();

private:
  std::string mInputFilePath;
};

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

class Assignment {
public:
  Assignment(const int aStart, const int aEnd);
  int getStart() const;
  int getEnd() const;
  bool contains(const Assignment &aOther);
  bool distinct(const Assignment &aOther);
  bool overlaps(const Assignment &aOther);

private:
  int mStart;
  int mEnd;
};

class AssignmentPair {
public:
  AssignmentPair(const Assignment &aFirst, const Assignment &aSecond);
  bool isContained();
  bool isOverlap();

private:
  Assignment mFirst;
  Assignment mSecond;
};

class CampCleanup {
public:
  CampCleanup(const std::string &aFilePath);
  int getContainedAssignments();
  int getOverlappingRanges();

private:
  std::vector<AssignmentPair> mAssignmentPairs;
};

Assignment::Assignment(const int aStart, const int aEnd)
    : mStart(aStart), mEnd(aEnd) {}

int Assignment::getStart() const { return mStart; }

int Assignment::getEnd() const { return mEnd; }

//! Determine if this assignment fully contains aOther
bool Assignment::contains(const Assignment &aOther) {
  return mStart <= aOther.getStart() && mEnd >= aOther.getEnd();
}

//! Determine if this assignment is distinct with aOther. An
//! assignment is "disticnt" if it doesn't have any overlapping
//! IDs with aOther.
bool Assignment::distinct(const Assignment &aOther) {
  return (aOther.getStart() > mEnd || aOther.getEnd() < mStart);
}

//! Determine if this assignment overlaps aOther
bool Assignment::overlaps(const Assignment &aOther) {
  return !distinct(aOther);
}

AssignmentPair::AssignmentPair(const Assignment &aFirst,
                               const Assignment &aSecond)
    : mFirst(aFirst), mSecond(aSecond) {}

//! @returns true if either assignment fully contains the other
bool AssignmentPair::isContained() {
  return mFirst.contains(mSecond) || mSecond.contains(mFirst);
}

bool AssignmentPair::isOverlap() { return mFirst.overlaps(mSecond); }
static Assignment readAssignment(const std::string &aString) {
  size_t delimiterPos = aString.find_first_of('-');
  int start = std::stoi(aString.substr(0, delimiterPos));
  int end = std::stoi(aString.substr(delimiterPos + 1));
  return Assignment(start, end);
}

static AssignmentPair readAssignmentPair(const std::string &aString) {
  size_t delimiterPos = aString.find_first_of(',');
  Assignment firstAssignment = readAssignment(aString.substr(0, delimiterPos));
  Assignment secondAssignment =
      readAssignment(aString.substr(delimiterPos + 1));
  return AssignmentPair(firstAssignment, secondAssignment);
}

static std::vector<AssignmentPair>
readAssignmentPairs(const std::string &aFilePath) {
  std::vector<AssignmentPair> assignmentPairs;
  std::string line;
  std::ifstream inputFile(aFilePath);
  assert(inputFile.is_open());
  while (std::getline(inputFile, line)) {
    assignmentPairs.push_back(readAssignmentPair(line));
  }
  return assignmentPairs;
}

CampCleanup::CampCleanup(const std::string &aFilePath)
    : mAssignmentPairs(readAssignmentPairs(aFilePath)) {}

int CampCleanup::getContainedAssignments() {
  int contained = 0;
  for (auto pair : mAssignmentPairs) {
    if (pair.isContained()) {
      contained++;
    }
  }
  return contained;
}

int CampCleanup::getOverlappingRanges() {
  int overlap = 0;
  for (auto pair : mAssignmentPairs) {
    if (pair.isOverlap()) {
      overlap++;
    }
  }
  return overlap;
}

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

TEST_CASE("Testing mostCalories") {
  const std::string testFilePath = "input/day/1/test";
  const std::string input = openTestFile(testFilePath);
  CalorieParser calorieParser(input);
  CHECK(calorieParser.mostCalories() == 24000);
}

TEST_CASE("Test topThreeTotal") {
  const std::string testFilePath = "input/day/1/test";
  const std::string input = openTestFile(testFilePath);
  CalorieParser calorieParser(input);
  CHECK(calorieParser.topThreeTotal() == 45000);
}

TEST_CASE("Test Total Score") {
  const std::string testFilePath = "input/day/2/test";
  RockPaperScissors rockPaperScissors(testFilePath);
  CHECK(rockPaperScissors.getTotalScore() == 45);
}

TEST_CASE("Test Total Priority") {
  const std::string testFilePath = "input/day/3/test.txt";
  RucksackReorganizer reorganizer(testFilePath);
  CHECK(157 == reorganizer.getTotalPriority());
}

TEST_CASE("Test Badge Priority") {
  const std::string testFilePath = "input/day/3/test.txt";
  RucksackReorganizer reorganizer(testFilePath);
  CHECK(70 == reorganizer.getBadgePriority());
}

TEST_CASE("Test Contained Assignments") {
  const std::string testFilePath = "input/day/4/test.txt";
  CampCleanup cleanup(testFilePath);
  CHECK(2 == cleanup.getContainedAssignments());
}

TEST_CASE("Test Overlapping Assignments") {
  const std::string testFilePath = "input/day/4/test.txt";
  CampCleanup cleanup(testFilePath);
  CHECK(4 == cleanup.getOverlappingRanges());
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
  // Set up doctest and run test cases first
  doctest::Context context;
  int res = context.run();
  if (context.shouldExit()) {
    return res;
  }

  std::string filePath = "input/day/1/input";
  std::ifstream inputFile(filePath);
  assert(inputFile.is_open());

  std::stringstream buffer;
  buffer << inputFile.rdbuf();
  CalorieParser calorieParser(buffer.str());
  std::cout << "The elf with the most calories has "
            << calorieParser.mostCalories() << " calories" << std::endl;
  std::cout << "The top three elves total " << calorieParser.topThreeTotal()
            << " calories" << std::endl;

  filePath = "input/day/2/input.txt";
  RockPaperScissors rockPaperScissors(filePath);
  std::cout << "Total score " << rockPaperScissors.getTotalScore() << std::endl;

  filePath = "input/day/3/input.txt";
  RucksackReorganizer reorganizer(filePath);
  std::cout << "Sum of priorities: " << reorganizer.getTotalPriority()
            << std::endl;
  std::cout << "Sum of badge priorities: " << reorganizer.getBadgePriority()
            << std::endl;

  filePath = "input/day/4/input.txt";
  CampCleanup campCleanup(filePath);
  std::cout << "Contained assignments: "
            << campCleanup.getContainedAssignments() << std::endl;
  std::cout << "Overlapping assignments: " << campCleanup.getOverlappingRanges()
            << std::endl;

  filePath = "input/day/5/input.txt";
  size_t numStacks = readNumStacks(filePath);
  std::vector<std::deque<char>> stacks = readStacks(filePath, numStacks);
  rearrangeCrates(filePath, stacks, true);
  std::cout << "Crate Mover 9000: " << getTopMessage(stacks) << std::endl;

  std::vector<std::deque<char>> secondStacks = readStacks(filePath, numStacks);
  rearrangeCrates(filePath, secondStacks, false);
  std::cout << "Crate Mover 9001: " << getTopMessage(secondStacks) << std::endl;
  return res;
}
