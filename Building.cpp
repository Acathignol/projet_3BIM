
#include "Building.h"

//=========================== Constructors =============================
Building::Building(){
  length_ = 0;
  width_ = 0;
  map_ = nullptr;
}

Building::Building(int length, int width){
  length_ = length;
  width_ = width;
  map_ = new int[length_*width_];
}

//=========================== Destructor ===============================
Building::~Building{
  delete[] map_;
  map_ = nullptr;
}

//=========================== Public Methods ===========================