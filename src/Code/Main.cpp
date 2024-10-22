#include "CalorieParser.hpp"
#include <fstream>
#include <iostream>
#include <set>
#include <string>

using namespace std;

int main(int argc, char **argv) {
  // Validate arguments
  if (argc != 2) {
    cout << "Usage: ./calories <path/to/input>" << endl;
    return 1;
  }

  // Open the file
  const std::string filePath = argv[1];
  ifstream inputFile(filePath);
  if (!inputFile.is_open()) {
    cout << "Cannot open file " << filePath << endl;
    return 1;
  }

  // Read file into set
  set<int, greater<int>> elfCalories = CalorieParser::parseCalories(inputFile);
  set<int>::iterator itr = elfCalories.begin();
  int most = *itr;
  cout << "Elf with the most calories has " << most << endl;
  itr++;
  int secondMost = *itr;
  itr++;
  int thirdMost = *itr;
  int topThreeTotal = most + secondMost + thirdMost;
  cout << "Top three Elves have " << topThreeTotal << endl;
  return 0;
}
