#include "RockPaperScissors.hpp"
#include <cassert>
#include <fstream>
#include <map>
#include <string>

enum GameToken {
  Rock,
  Paper,
  Scissors,
};

enum DesiredOutcome { Win, Loss, Draw };

const std::map<std::string, GameToken> opponentEncoding{
    {"A", GameToken::Rock},
    {"B", GameToken::Paper},
    {"C", GameToken::Scissors}};

const std::map<std::string, DesiredOutcome> outcomeEncoding{
    {"X", DesiredOutcome::Loss},
    {"Y", DesiredOutcome::Draw},
    {"Z", DesiredOutcome::Win}};

GameToken opponentStringToToken(const std::string &aString) {
  auto itr = opponentEncoding.find(aString);
  assert(itr != opponentEncoding.end());
  return itr->second;
}

DesiredOutcome parseOutcomeString(const std::string &aString) {
  auto itr = outcomeEncoding.find(aString);
  assert(itr != outcomeEncoding.end());
  return itr->second;
}

GameToken determinePlayerToken(const DesiredOutcome &aOutcome,
                               const GameToken &aOpponentToken) {
  if (aOutcome == DesiredOutcome::Draw) {
    return aOpponentToken;
  } else if (aOutcome == DesiredOutcome::Loss) {
    if (aOpponentToken == GameToken::Rock) {
      return GameToken::Scissors;
    } else if (aOpponentToken == GameToken::Paper) {
      return GameToken::Rock;
    } else {
      // Opponent played Scissors
      return GameToken::Paper;
    }
  } else {
    if (aOpponentToken == GameToken::Rock) {
      return GameToken::Paper;
    } else if (aOpponentToken == GameToken::Paper) {
      return GameToken::Scissors;
    } else {
      // Opponent played Scissors
      return GameToken::Rock;
    }
  }
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
int scoreOutcome(const DesiredOutcome &aOutcome) {
  switch (aOutcome) {
  case DesiredOutcome::Loss:
    return 0;
  case DesiredOutcome::Draw:
    return 3;
  case DesiredOutcome::Win:
    return 6;
  }
}

// Calculate the score for a round. The score for a round is the score of the
// player's selected token added with the outcome of the game.
int scoreRound(const GameToken &aPlayerToken, const DesiredOutcome &aOutcome) {
  return scoreToken(aPlayerToken) + scoreOutcome(aOutcome);
}

// Parse the input game by game
RockPaperScissors::RockPaperScissors(const std::string &aFilePath)
    : mTotalScore(0) {
  std::string line = "";
  std::string delimiter = " ";
  std::ifstream inputFile(aFilePath);
  assert(inputFile.is_open());
  while (std::getline(inputFile, line)) {
    size_t pos = line.find(delimiter);
    GameToken opponentToken = opponentStringToToken(line.substr(0, pos));
    line.erase(0, pos + delimiter.length());
    DesiredOutcome outcome = parseOutcomeString(line);
    GameToken playerToken = determinePlayerToken(outcome, opponentToken);
    mTotalScore += scoreRound(playerToken, outcome);
  }
}

unsigned int RockPaperScissors::getTotalScore() { return mTotalScore; }
