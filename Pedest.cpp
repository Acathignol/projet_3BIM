//=========================== Includes =================================

#include "Pedest.h"

using namespace std;

//================= Definition of static attributes ====================

int Pedest::RMAX = 6; // 60cm de rayon
int Pedest::RMIN = 4; // 40cm de rayon
int Pedest::EQSPEEDMIN = 4;
int Pedest::EQSPEEDMAX = 7;
int Pedest::MODEL = 1;
double Pedest::ZONE_XMIN = 0;
double Pedest::ZONE_XMAX = 0;
double Pedest::ZONE_YMIN = 0;
double Pedest::ZONE_YMAX = 0;

//=========================== Constructors =============================

Pedest::Pedest() {
  x_ = 0;
  y_ = 0;
  radius_ = 0;
  mood_ = 0;
  img_ = CircleShape();
  speed_ = 0;
  eq_speed_ = 0;
}

Pedest::Pedest(const int startX, const int startY, int zoom){
  x_ = startX;
  y_ = startY;
  unsigned int r = rand()%(Pedest::RMAX-Pedest::RMIN)+Pedest::RMIN;
  radius_ = (float) r;
  mood_ = 0;
  img_ = CircleShape(r);
  img_.setPosition(zoom*x_ - r, zoom*y_ - r);
  img_.setFillColor(Color(Color::Green));
  speed_ = 0;
  eq_speed_ = 0.1*( (double) (rand()%(Pedest::EQSPEEDMAX-Pedest::EQSPEEDMIN)+Pedest::EQSPEEDMIN) );
}

Pedest::Pedest(const Pedest& model){
  x_ = model.x_;
  y_ = model.y_;
  radius_ = model.radius_;
  mood_ = model.mood_;
  img_ = model.img_;
  speed_ = model.speed_;
  eq_speed_ = model.eq_speed_;
}

void Pedest::operator=(const Pedest& model){
  x_ = model.x_;
  y_ = model.y_;
  radius_ = model.radius_;
  mood_ = model.mood_;
  img_ = model.img_;
  speed_ = model.speed_;
  eq_speed_ = model.eq_speed_;
}

//=========================== Public Methods ===========================

void Pedest::move(double x_move , double y_move , double new_speed, int zoom){
  x_ += x_move;
  y_ += y_move;
  img_.setPosition(zoom*x_ -radius_, zoom*y_ -radius_);
  speed_ = new_speed;
}

