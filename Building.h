
#ifndef Building_h
#define Building_h

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "ImagePPM.h"

using namespace std;

class Building {
public:
  // =========================== Constructors ==========================
  
  Building();
  Building(int length, int width);
  Building(const ImagePPM& model);
  
  // =========================== Destructor ============================
  
  ~Building();
  
  // =========================== Getters ===============================
  
  inline int length() const;
  inline int width() const;
  inline int* map() const;
  inline int map(size_t x, size_t y) const;
  
  // =========================== Setters ===============================
  
  inline void setValue(size_t x, size_t y, int value);
  
  // =========================== Public Methods ========================
  
  int whatIsThis();
  void fillCopyMap(int** copyMap);
  std::vector<int> testLine(int x, int y);
  bool checkSides(int x , int y);
  void testAnswer(int x, int y , std::vector<int> test, int** copyMap);
  //~ bool crossing(std::vector<int> v);
  //~ bool merging(std::vector<int> v);
  //~ bool angle(std::vector<int> v);
  //~ bool corridor(std::vector<int> v);
  
  std::vector<int> sides(int hole, div_t divresult);


  void drawMap(void) const;
  void drawTrajectory(vector<pair<int, int>> way) const;
  
protected:
  int length_;
  int width_;
  int* map_;

};

//========================Inline functions' definition==================

inline int Building::length() const{
  return length_;
}

inline int Building::width() const{
  return width_;
}

inline int* Building::map() const{
  return map_;
}

inline int Building::map(size_t x, size_t y) const{
  return map_[width_*y+x];
}

inline void Building::setValue(size_t x, size_t y, int value){
  map_[width_*y+x] = value;
}

#endif /* Building_h */
