
#ifndef Pedest_H__
#define Pedest_H__

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Pedest {
 public :
  // =========================== Constructors ==========================
  
  Pedest();
  Pedest(const int startX, const int startY, const float radius,
         const int* map, const int W, const int H);
  
  //=========================== Destructor =============================
  
  ~Pedest();

  // =========================== Getters ===============================
  
  inline int x() const;
  inline int y() const;
  inline vector<pair<int, int>> pathToExit(void) const;
  
  //=========================== Setters ================================
  
  void xpp(const double new_xpp);
  void ypp(const double new_ypp);
  void set_mood(const int new_mood);
  void accelerate();
  void brake();
  vector<pair<int, int>> findExit(const pair<int, int>& start, const int* map,
                         const int W, const int H);
  
  //=========================== Operators ==============================

  //=========================== Public Methods =========================
  
  void move();

protected :
  //=========================== Protected Methods ======================
  
  
  
  //=========================== Attributes =============================
  
  double x_;
  double y_;
  float radius_;
  double xp_;
  double yp_;
  double xpp_;
  double ypp_;
  int mood_;
  vector<pair<int, int>>* path_to_exit_;
  
};

//========================Inline functions' definition==================

inline int Pedest::x() const{
  return x_;
}

inline int Pedest::y() const{
  return y_;
}

inline vector<pair<int, int>> Pedest::pathToExit(void) const{
  return *path_to_exit_;
}

#endif // Pedest_H__
