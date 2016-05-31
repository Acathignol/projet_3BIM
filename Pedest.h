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
  // =========================== Static attributes =====================
  
  
  // =========================== Constructors ==========================
  
  Pedest();
  Pedest(const int startX, const int startY);
  Pedest(const Pedest& model);
  void operator=(const Pedest& model);
  
  //=========================== Destructor =============================
  
  ~Pedest();

  // =========================== Getters ===============================
  
  inline int x() const;
  inline int y() const;
  //~ inline vector<pair<int, int>> pathToExit(void) const;
  inline CircleShape img() const;
  inline double speed(void) const;
  inline double eqSpeed(void) const;
  inline float radius(void) const;
  
  //=========================== Setters ================================
  
  inline void set_mood(const int new_mood);
  //~ vector<pair<int, int>> findExit(const pair<int, int>& start, const int* map,
                         //~ const int W, const int H);
  
  //=========================== Public Methods =========================
  void move(double x_move , double y_move , double new_speed);

protected :
  //=========================== Attributes =============================
  
  double x_;
  double y_;
  float radius_;
  int mood_;
  //~ vector<pair<int, int>> path_to_exit_;
  CircleShape img_;
  double speed_;
  double eq_speed_;
  
};

//========================Inline functions' definition==================

inline int Pedest::x() const{ return x_; }
inline int Pedest::y() const{ return y_; }
inline void Pedest::set_mood(const int new_mood){ mood_ = new_mood; }
//~ inline vector<pair<int, int>> Pedest::pathToExit(void) const{ return path_to_exit_; }
inline CircleShape Pedest::img(void) const{ return img_; }
inline double Pedest::speed() const { return speed_; }
inline double Pedest::eqSpeed() const { return eq_speed_; }
inline float Pedest::radius() const { return radius_; }


#endif // Pedest_H__
