
//=========================== Includes =================================
#include "Point.h"

Point::Point(void){
  x_ = 0;
  y_ = 0;
}

Point::Point(int x, int y) {
  x_ = x;
  y_ = y;
}

void Point::display(void) {
  cout << '(' << x_ << ',' << y_ << ')' <<endl;
}
