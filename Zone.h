#ifndef Zone_h
#define Zone_h

#include "Pedest.h"

using namespace std;

class Zone {
 public:
  // =========================== Static attributes =====================
  
  
  // =========================== Constructors ==========================
  
  Zone(int xmin, int xmax, int ymin, int ymax, int* map, int W, int H);
  
  // =========================== Destructor ============================
  
  ~Zone();
  
  // =========================== Getters ===============================
  
  inline int direction() const;
  
  // =========================== Setters ===============================
  
  inline void setDirection(int dir);
  
  // =========================== Public Methods ========================
  
  bool isExit(void);
  
 protected:
  //======================== Attributes ==================================
  int xmin_;
  int xmax_;
  int ymin_;
  int ymax_;
  int direction_;
  int* building_map_;
  int building_width_;
  int building_length_;

};

//========================Inline functions' definition==================

inline int Zone::direction() const{ return direction_; }
inline void Zone::setDirection(int dir) { direction_ = dir; }

#endif /* Zone_h */
