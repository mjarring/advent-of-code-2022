#include <string>

class RucksackReorganizer {
public:
  RucksackReorganizer(const std::string &aFilePath);
  int getTotalPriority();
  int getBadgePriority();

private:
  std::string mInputFilePath;
};
