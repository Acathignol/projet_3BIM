#ifndef Pedest_H__
#define Pedest_H__

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include <SFML/Graphics.hpp>


using namespace std;
using namespace sf;

class Pedest {
 public :
  //================= Definition of static attributes ====================

  static int RMAX;
  static int RMIN;
  static int EQSPEEDMIN;
  static int EQSPEEDMAX;
  static int MODEL;
  static double ZONE_XMIN;
  static double ZONE_XMAX;
  static double ZONE_YMIN;
  static double ZONE_YMAX;
  
  
  // =========================== Constructors ==========================
  
  Pedest();
  Pedest(const int startX, const int startY, int zoom);
  void operator=(const Pedest& model);
  
  // =========================== Getters ===============================
  
  inline double x() const;
  inline double y() const;
  inline CircleShape img() const;
  inline double speed(void) const;
  inline double eqSpeed(void) const;
  inline float radius(void) const;
  
  //=========================== Setters ================================
  
  inline void set_mood(const int new_mood);
  
  //=========================== Public Methods =========================

  void move(double x_move , double y_move , double new_speed, int zoom);

 protected :
  //=========================== Attributes =============================
  
  double x_;
  double y_;
  float radius_;
  int mood_;
  CircleShape img_;
  double speed_;
  double eq_speed_;
  
};

//========================Inline functions' definition==================

inline double Pedest::x() const{ return x_; }
inline double Pedest::y() const{ return y_; }
inline void Pedest::set_mood(const int new_mood){ mood_ = new_mood; }
inline CircleShape Pedest::img(void) const{ return img_; }
inline double Pedest::speed() const { return speed_; }
inline double Pedest::eqSpeed() const { return eq_speed_; }
inline float Pedest::radius() const { return radius_; }

#endif // Pedest_H__
