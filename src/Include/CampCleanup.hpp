#include <string>

class CampCleanup {
public:
  CampCleanup(const std::string &aFilePath);
  int getContainedAssignments();

private:
  std::string mInputFilePath;
};
