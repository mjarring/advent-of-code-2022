#include "CampCleanup.hpp"
#include <cassert>
#include <fstream>
#include <string>
#include <vector>

class Assignment {
public:
  Assignment(const int aStart, const int aEnd) : mStart(aStart), mEnd(aEnd) {}
  int getStart() const { return mStart; }
  int getEnd() const { return mEnd; }
  //! Determine if this assignment fully contains aOther
  bool contains(const Assignment &aOther) {
    return mStart <= aOther.getStart() && mEnd >= aOther.getEnd();
  }

private:
  int mStart;
  int mEnd;
};

class AssignmentPair {
public:
  AssignmentPair(const Assignment &aFirst, const Assignment &aSecond)
      : mFirst(aFirst), mSecond(aSecond) {}
  //! @returns true if either assignment fully contains the other
  bool isContained() {
    return mFirst.contains(mSecond) || mSecond.contains(mFirst);
  }

private:
  Assignment mFirst;
  Assignment mSecond;
};

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
    : mInputFilePath(aFilePath) {}

int CampCleanup::getContainedAssignments() {
  std::vector<AssignmentPair> assignmentPairs =
      readAssignmentPairs(mInputFilePath);
  int contained = 0;
  for (auto pair : assignmentPairs) {
    if (pair.isContained()) {
      contained++;
    }
  }
  return contained;
}
