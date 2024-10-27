#include "RockPaperScissors.hpp"
#include <cassert>
#include <map>
#include <sstream>
#include <string>

enum GameToken {
  Rock,
  Paper,
  Scissors,
};

const std::map<std::string, GameToken> strategyGuideEncodng{
    {"A", GameToken::Rock},     {"B", GameToken::Paper},
    {"C", GameToken::Scissors}, {"X", GameToken::Rock},
    {"Y", GameToken::Paper},    {"Z", GameToken::Scissors}};

GameToken stringToToken(const std::string &aString) {
  auto itr = strategyGuideEncodng.find(aString);
  assert(itr != strategyGuideEncodng.end());
  return itr->second;
}

// Score the player's selected token
int scoreToken(const GameToken &aToken) {
  switch (aToken) {
  case GameToken::Rock:
    return 1;
  case GameToken::Paper:
    return 2;
  case GameToken::Scissors:
    return 3;
  }
}

// Score the outcome of a game (win or loss for the player)
int scoreOutcome(const GameToken &aOpponent, const GameToken &aPlayer) {
  if (aOpponent == aPlayer) {
    // Draw is 3
    return 3;
  } else if ((aOpponent == GameToken::Rock && aPlayer == GameToken::Scissors) ||
             (aOpponent == GameToken::Paper && aPlayer == GameToken::Rock) ||
             (aOpponent == GameToken::Scissors &&
              aPlayer == GameToken::Paper)) {
    // Player loss is 0
    return 0;
  } else {
    // Player win is 6
    return 6;
  }
}

// Calculate the score for a round. The score for a round is the score of the
// player's selected token added with the outcome of the game.
int scoreRound(const GameToken &aOpponentToken, const GameToken &aPlayerToken) {
  return scoreToken(aPlayerToken) + scoreOutcome(aOpponentToken, aPlayerToken);
}

// Parse the input game by game
RockPaperScissors::RockPaperScissors(const std::string &aInput)
    : mTotalScore(0) {
  std::string line = "";
  std::string delimiter = " ";
  std::stringstream stream(aInput);
  while (std::getline(stream, line)) {
    size_t pos = line.find(delimiter);
    GameToken opponentToken = stringToToken(line.substr(0, pos));
    line.erase(0, pos + delimiter.length());
    GameToken playerToken = stringToToken(line);
    mTotalScore += scoreRound(opponentToken, playerToken);
  }
}

int RockPaperScissors::getTotalScore() { return mTotalScore; }
