#include <string>

class RucksackReorganizer {
public:
  RucksackReorganizer(const std::string &aFilePath);
  int getTotalPriority();

private:
  int mTotalPriority;
};
