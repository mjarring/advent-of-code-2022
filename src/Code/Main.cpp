#include "CalorieParser.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

static const std::string CALORIES = "calories";

int main(int argc, char **argv) {
  // Validate arguments
  if (argc != 3) {
    cout << "Usage: ./advent function input" << endl;
    return 1;
  }

  // Open the file
  const std::string filePath = argv[2];
  ifstream inputFile(filePath);
  if (!inputFile.is_open()) {
    cout << "Cannot open file " << filePath << endl;
    return 1;
  }

  // Determine the function
  const std::string function = argv[1];
  if (CALORIES == function) {
    std::stringstream buffer;
    buffer << inputFile.rdbuf();
    CalorieParser calorieParser(buffer.str());
    calorieParser.solve();
  }

  return 0;
}
