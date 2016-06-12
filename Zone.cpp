
#include "Zone.h"

//================= Definition of static attributes ====================

//=========================== Constructors =============================

Zone::Zone(int xmin, int xmax, int ymin, int ymax, int* map, int W, int H){
  xmin_ = xmin;
  xmax_ = xmax;
  ymin_ = ymin;
  ymax_ = ymax;
  building_map_ = map;
  building_width_ = W;
  building_length_ = H;
  direction_ = 10;
}

//=========================== Destructor ===============================

Zone::~Zone(){
  
}

//=========================== Public Methods ===========================

bool Zone::isExit(void){
  if (not (xmin_==0 or ymin_==0 or xmax_==building_width_-1 or ymax_==building_length_-1)){
    return false;
  }
  if (xmin_ == 0 and not building_map_[(1+ymin_)*building_width_]) return true;
  if (xmax_ == building_width_-1 and not building_map_[(1+ymin_)*building_width_+xmax_]) return true;
  if (ymin_ == 0 and not building_map_[1+xmin_]) return true;
  if (ymax_ == building_length_-1 and not building_map_[ymax_*building_width_+xmin_+1]) return true;
  return false;
}
