#include "RockPaperScissors.hpp"
#include <map>
#include <string>

const std::map<RockPaperScissors::GameToken, std::string> strategyGuideEncodng{
    {RockPaperScissors::GameToken::OpponentRock, "A"},
    {RockPaperScissors::GameToken::OpponentPaper, "B"},
    {RockPaperScissors::GameToken::OpponentScissors, "C"},
    {RockPaperScissors::GameToken::PlayerRock, "X"},
    {RockPaperScissors::GameToken::PlayerPaper, "Y"},
    {RockPaperScissors::GameToken::PlayerScissors, "Z"}};

RockPaperScissors::RockPaperScissors(const std::string &aInput) {}

int RockPaperScissors::totalScore() { return 1; }

int RockPaperScissors::scoreRound(const GameToken &aOpponentToken,
                                  const GameToken &aPlayerToken) {
  return 1;
}
