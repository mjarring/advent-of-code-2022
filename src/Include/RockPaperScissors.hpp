#include <string>

class RockPaperScissors {
public:
  RockPaperScissors(const std::string &aFilePath);
  unsigned int getTotalScore();

private:
  unsigned int mTotalScore;
};
