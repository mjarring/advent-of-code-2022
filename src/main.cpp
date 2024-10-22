#include <fstream>
#include <iostream>
#include <set>
#include <string>

using namespace std;

set<int, greater<int>> parseElfCalories(ifstream &aFile) {
  set<int, greater<int>> elfCalories;
  int currentCalories = 0;
  string line;
  while (getline(aFile, line)) {
    if (line.empty()) {
      // We have reached the end of this elf's calorie count
      // Store the caloreis for this elf in the set
      elfCalories.insert(currentCalories);
      // Reset the calorie count for the current elf
      currentCalories = 0;
    } else {
      // Assume this is a number
      int number = stoi(line);
      // Add this number to the calorie count for current elf
      currentCalories += number;
    }
  }
  return elfCalories;
}

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
  set<int, greater<int>> elfCalories = parseElfCalories(inputFile);
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
