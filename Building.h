#ifndef Building_h
#define Building_h

#include "Pedest.h"
#include <SFML/Window.hpp>
#include <math.h>
#include <time.h>

using namespace std;
using namespace sf;

class Building {
 public:
  // =========================== Static attributes =====================
  
  static int NPEDEST;
  static int ZOOM;
  
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
  inline vector<float> xborders() const;
  inline vector<float> yborders() const;
  inline Pedest people(const int i) const;
  
  // =========================== Setters ===============================
  
  inline void setValue(size_t x, size_t y, int value);
  
  // =========================== Public Methods ========================
  
  void drawMap(int* nodemap_, int w , int l) const;
  void drawData(int* nodemap_, int w , int l) const;
  void drawTrajectory(int* nodemap_, int w, int l, vector<pair<int, int>> way) const;
  void movePeople(void);
  unsigned int getDirection(double x, double y);
  bool notEmpty(void) const;
  vector<pair<int, int>> findExit(const pair<int, int>& start, int* map, int W, int H);  
  
 protected:
  //======================== Attributes ==================================
  int length_;
  int width_;
  int* map_;
  int* will_tab;
  vector<RectangleShape> walls_;
  vector<float> xborders_;
  vector<float> yborders_;
  Pedest* people_;

};

//========================Inline functions' definition==================

inline int Building::length() const{ return length_; }
inline int Building::width() const{ return width_; }
inline int* Building::map() const{ return map_; }
inline int Building::map(size_t x, size_t y) const{ return map_[width_*y+x]; }
inline void Building::setValue(size_t x, size_t y, int value){ map_[width_*y+x] = value; }
inline vector<RectangleShape> Building::walls() const { return walls_; }
inline vector<float> Building::xborders() const { return xborders_; }
inline vector<float> Building::yborders() const { return yborders_; }
inline Pedest Building::people(const int i) const { return people_[i]; }

#endif /* Building_h */
