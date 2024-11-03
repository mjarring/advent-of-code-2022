#include "CampCleanup.hpp"
#include <cassert>
#include <fstream>
#include <string>
#include <vector>

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
