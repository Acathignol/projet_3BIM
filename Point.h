
#ifndef Point_H__
#define Point_H__

#include <iostream>

using namespace std;

class Point{
 public :
  Point();
  Point(int x, int y);
  inline int x(void) const;
  inline int y(void) const;
  inline void set(int x, int y);
  void display(void);
  inline int coord_in(int W) const;
 protected :
  int x_;
  int y_;
};

inline int Point::x(void) const { return x_; }
inline int Point::y(void) const { return y_; }
inline void Point::set(int x, int y) { x_ = x;  y_ = y; }
inline int Point::coord_in(int W) const { return x_+ W *y_; }
#endif // Point_H__
