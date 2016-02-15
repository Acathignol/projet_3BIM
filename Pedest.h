
#ifndef Pedest_H__
#define Pedest_H__




class Pedest {
 public :
  // =========================== Constructors ==========================
  Pedest();
  Pedest(const int startX, const int startY);
  //=========================== Destructor =============================

  // =========================== Getters ===============================
  int x();
  int y();
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



#endif // Pedest_H__
