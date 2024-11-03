class Assignment {
public:
  Assignment(const int aStart, const int aEnd);
  int getStart() const;
  int getEnd() const;
  bool contains(const Assignment &aOther);
  bool distinct(const Assignment &aOther);
  bool overlaps(const Assignment &aOther);

private:
  int mStart;
  int mEnd;
};

class AssignmentPair {
public:
  AssignmentPair(const Assignment &aFirst, const Assignment &aSecond);
  bool isContained();
  bool isOverlap();

private:
  Assignment mFirst;
  Assignment mSecond;
};
