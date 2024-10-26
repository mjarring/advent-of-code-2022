#include <string>

class RockPaperScissors {
public:
  enum GameToken {
    PlayerRock,
    PlayerPaper,
    PlayerScissors,
    OpponentRock,
    OpponentPaper,
    OpponentScissors
  };

  RockPaperScissors(const std::string &aInput);
  int totalScore();

private:
  int scoreRound(const GameToken &aOpponentToken,
                 const GameToken &aPlayerToken);
};
