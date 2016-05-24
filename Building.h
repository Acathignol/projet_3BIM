#ifndef SFML_H
#define SFML_H
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#endif /* SFML_H */

#ifndef Building_h
#define Building_h

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>


using namespace std;
using namespace sf;

class Building {
public:
  // =========================== Constructors ==========================
  
  Building();
  Building(int length, int width);
  Building(const string& filename);
  
  // =========================== Destructor ============================
  
  ~Building();
  
  // =========================== Getters ===============================
  
  inline int length() const;
  inline int width() const;
  inline int* map() const;
  inline int map(size_t x, size_t y) const;
  inline vector<RectangleShape> walls() const;
  
  // =========================== Setters ===============================
  
  inline void setValue(size_t x, size_t y, int value);
  
  // =========================== Public Methods ========================


  pair<vector<int>,vector<int>> vectorEdges2D();
  pair<vector<int>,vector<int>> testAnswer2D(int x, int y , vector<int> test, pair<vector<int>,vector<int>> result);
  vector<int> vectorEdges();
  vector<int> testLine(int x, int y);
  bool checkSides(int x , int y);
  vector<int> testAnswer(int x, int y , vector<int> test, vector<int> result);
  void drawMap(void) const;
  void drawTrajectory(vector<pair<int, int>> way) const;
  
protected:
  //======================== Attributes ==================================
  int length_;
  int width_;
  int* map_;
  vector<RectangleShape> walls_;

};

//========================Inline functions' definition==================

inline int Building::length() const{ return length_; }
inline int Building::width() const{ return width_; }
inline int* Building::map() const{ return map_; }
inline int Building::map(size_t x, size_t y) const{ return map_[width_*y+x]; }
inline void Building::setValue(size_t x, size_t y, int value){ map_[width_*y+x] = value; }
inline vector<RectangleShape> Building::walls() const { return walls_; }

#endif /* Building_h */
