#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

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

const std::string testFilePath = "input/day/4/test.txt";

TEST_CASE("Test Contained Assignments") {
  CampCleanup cleanup(testFilePath);
  CHECK(2 == cleanup.getContainedAssignments());
}

TEST_CASE("Test Overlapping Assignments") {
  CampCleanup cleanup(testFilePath);
  CHECK(4 == cleanup.getOverlappingRanges());
}

int main() {
  // Set up doctest and run test cases first
  doctest::Context context;
  int res = context.run();
  if (context.shouldExit()) {
    return res;
  }

  const std::string filePath = "input/day/4/input.txt";
  CampCleanup campCleanup(filePath);
  std::cout << "Contained assignments: "
            << campCleanup.getContainedAssignments() << std::endl;
  std::cout << "Overlapping assignments: " << campCleanup.getOverlappingRanges()
            << std::endl;
}
