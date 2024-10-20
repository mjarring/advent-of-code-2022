#include <fstream>
#include <iostream>
#include <set>
#include <string>

using namespace std;

int main() {
  set<int, greater<int>> elfCalories;
  int currentCalories = 0;
  ifstream inputFile("input");
  if (inputFile.is_open()) {
    string line;
    while (getline(inputFile, line)) {
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
  } else {
    cout << "File not found!" << endl;
    return 1;
  }
  set<int>::iterator itr = elfCalories.begin();
  int most = *itr;
  itr++;
  int secondMost = *itr;
  itr++;
  int thirdMost = *itr;
  int total = most + secondMost + thirdMost;
  cout << "Most Calories: " << total << endl;
  return 0;
}
