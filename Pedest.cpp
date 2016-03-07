
//=========================== Includes =================================
#include "Pedest.h"

using namespace std;

//================= Definition of static attributes ====================


//=========================== Constructors =============================
Pedest::Pedest() {
  x_ = 0;
  y_ = 0;
  radius_ = 0;
  xp_ = 1.0;
  yp_ = 1.0;
  xpp_ = 0.0;
  ypp_ = 0.0;
  mood_ = 0;
  path_to_exit_ = nullptr;
}

Pedest::Pedest(const int startX, const int startY, const float radius,const int* map){
  x_ = startX;
  y_ = startY;
  radius_ = radius;
  xp_ = 0.0;
  yp_ = 0.0;
  xpp_ = 0.0;
  ypp_ = 0.0;
  mood_ = 0;
  path_to_exit_ = new vector<Point> (findExit(map));
}

//=========================== Destructor ===============================

Pedest::~Pedest(void){
  delete path_to_exit_;
}

//=========================== Public Methods ===========================


void Pedest::xpp(const double new_xpp){
  xpp_ = new_xpp;
}

void Pedest::ypp(const double new_ypp){
  ypp_ = new_ypp;
}

void Pedest::set_mood(const int new_mood){
  mood_ = new_mood;
}

void Pedest::move(){
  x_ += xp_;
  y_ += yp_;
}

void Pedest::accelerate(){
  if (xpp_ == 0) xpp_ = 0.75;
  if (ypp_ == 0) ypp_ = 0.75;
  xpp_ *= 1.5;
  ypp_ *= 1.5;
  xp_ += xpp_;
  yp_ += ypp_;
}

void Pedest::brake(){
  xp_ -= xpp_;
  yp_ -= ypp_;
  xpp_ = xpp_ /1.5;
  ypp_ = ypp_ /1.5;
  if (xpp_ < 0.1) xpp_ = 0;
  if (ypp_ < 0.1) ypp_ = 0;
}

vector<Point> Pedest::findExit(const int* map){
  vector<Point> A (1, Point(2,2) ); //N'importe quoi en attendant de coder le flood
  return A;
}

//=========================== Protected Methods ========================

//=========================== Functions ================================
