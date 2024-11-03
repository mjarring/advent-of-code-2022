#include "Assignment.hpp"
#include <string>
#include <vector>

class CampCleanup {
public:
  CampCleanup(const std::string &aFilePath);
  int getContainedAssignments();
  int getOverlappingRanges();

private:
  std::vector<AssignmentPair> mAssignmentPairs;
};
