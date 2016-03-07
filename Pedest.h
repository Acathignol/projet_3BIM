
#ifndef Pedest_H__
#define Pedest_H__

#include <cstdio>
#include <cstdlib>
#include <iostream>


class Pedest {
 public :
  // =========================== Constructors ==========================
  Pedest();
  Pedest(const int startX, const int startY, const float radius);
  //=========================== Destructor =============================
  ~Pedest();

  // =========================== Getters ===============================
  inline int x() const;
  inline int y() const;
  //=========================== Setters ================================
  void xpp(const double new_xpp);
  void ypp(const double new_ypp);
  void set_mood(const int new_mood);
  void accelerate();
  void brake();
  //=========================== Operators ==============================

  //=========================== Public Methods =========================
  void move();

protected :
  //=========================== Protected Methods ======================
  
  //=========================== Attributes =============================
  int x_;
  int y_;
  float radius_;
  double xp_;
  double yp_;
  double xpp_;
  double ypp_;
  int mood_;
};




//===========================Getters' definitions=======================

//===========================Setters' definitions=======================

//===========================Operators' definitions=====================

//========================Inline functions' definition==================
inline int Pedest::x() const{
  return x_;
}

inline int Pedest::y() const{
  return y_;
}

#endif // Pedest_H__
