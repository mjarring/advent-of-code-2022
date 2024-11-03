#include "Assignment.hpp"

Assignment::Assignment(const int aStart, const int aEnd)
    : mStart(aStart), mEnd(aEnd) {}

int Assignment::getStart() const { return mStart; }

int Assignment::getEnd() const { return mEnd; }

//! Determine if this assignment fully contains aOther
bool Assignment::contains(const Assignment &aOther) {
  return mStart <= aOther.getStart() && mEnd >= aOther.getEnd();
}

//! Determine if this assignment is distinct with aOther. An
//! assignment is "disticnt" if it doesn't have any overlapping
//! IDs with aOther.
bool Assignment::distinct(const Assignment &aOther) {
  return (aOther.getStart() > mEnd || aOther.getEnd() < mStart);
}

//! Determine if this assignment overlaps aOther
bool Assignment::overlaps(const Assignment &aOther) {
  return !distinct(aOther);
}

AssignmentPair::AssignmentPair(const Assignment &aFirst,
                               const Assignment &aSecond)
    : mFirst(aFirst), mSecond(aSecond) {}

//! @returns true if either assignment fully contains the other
bool AssignmentPair::isContained() {
  return mFirst.contains(mSecond) || mSecond.contains(mFirst);
}

bool AssignmentPair::isOverlap() { return mFirst.overlaps(mSecond); }
