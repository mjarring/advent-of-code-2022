#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
  int mostCalories = 0;
  int currentCalories = 0;
  ifstream inputFile("input");
  if (inputFile.is_open()) {
    string line;
    while (getline(inputFile, line)) {
      if (line.empty()) {
        // We have reached the end of this elf's calorie count
        if (currentCalories > mostCalories) {
          // This elf is carrying the most calories
          mostCalories = currentCalories;
        }
        // Reset the calorie count for the current elf
        currentCalories = 0;
      } else {
        // Assume this is a number
        int number = stoi(line);
        // Add this number to the calorie count for current elf
        currentCalories += number;
      }
    }
  } else {
    cout << "File not found!" << endl;
    return 1;
  }
  cout << "Most Calories: " << mostCalories << endl;
  return 0;
}
