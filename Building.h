#ifndef Building_h
#define Building_h

#include "Pedest.h"
#include <SFML/Window.hpp>

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
  inline vector<int> xborders() const;
  inline vector<int> yborders() const;
  inline Pedest people(const int i) const;
  
  // =========================== Setters ===============================
  
  inline void setValue(size_t x, size_t y, int value);
  
  // =========================== Public Methods ========================
  
  void drawMap(void) const;
  void drawTrajectory(vector<pair<int, int>> way) const;
  void movePeople(void);
  unsigned int getDirection(unsigned int x, unsigned int y);
  double getZoneLimNear(unsigned int x, unsigned int y, unsigned int main_dir );
  vector<Pedest> scanZone(double zone_xmin, double zone_xmax, double zone_ymin, double zone_ymax);
  bool notEmpty(void) const;
  
 protected:
  //======================== Attributes ==================================
  int length_;
  int width_;
  int* map_;
  vector<RectangleShape> walls_;
  vector<int> xborders_;
  vector<int> yborders_;
  Pedest* people_;

};

//========================Inline functions' definition==================

inline int Building::length() const{ return length_; }
inline int Building::width() const{ return width_; }
inline int* Building::map() const{ return map_; }
inline int Building::map(size_t x, size_t y) const{ return map_[width_*y+x]; }
inline void Building::setValue(size_t x, size_t y, int value){ map_[width_*y+x] = value; }
inline vector<RectangleShape> Building::walls() const { return walls_; }
inline vector<int> Building::xborders() const { return xborders_; }
inline vector<int> Building::yborders() const { return yborders_; }
inline Pedest Building::people(const int i) const { return people_[i]; }

#endif /* Building_h */
