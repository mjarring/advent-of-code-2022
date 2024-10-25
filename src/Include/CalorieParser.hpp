#include <functional>
#include <set>
#include <string>

class CalorieParser {
public:
  CalorieParser(const std::string &aInput);
  void solve();

private:
  std::set<int, std::greater<int>> mElfCalories;
};
