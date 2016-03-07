
#ifndef Point_H__
#define Point_H__

class Point{
 public :
 Point();
  Point(int x, int y);
  inline int x(void) const;
  inline int y(void) const;
 protected :
  int x_;
  int y_;
};

inline int Point::x(void) const { return x_; }
inline int Point::y(void) const { return y_; }
#endif // Point_H__
