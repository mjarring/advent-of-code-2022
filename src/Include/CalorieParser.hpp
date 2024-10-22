#include <fstream>
#include <functional>
#include <set>

using namespace std;

class CalorieParser {
public:
  static set<int, greater<int>> parseCalories(ifstream &aFile);
};
