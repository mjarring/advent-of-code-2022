#include <functional>
#include <set>
#include <string>

class CalorieParser {
public:
  CalorieParser(const std::string &aInput);
  int mostCalories();
  int topThreeTotal();

private:
  std::set<int, std::greater<int>> mElfCalories;
};
