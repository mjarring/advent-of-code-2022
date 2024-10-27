#include <string>

class RockPaperScissors {
public:
  RockPaperScissors(const std::string &aInput);
  int getTotalScore();

private:
  int mTotalScore;
};
