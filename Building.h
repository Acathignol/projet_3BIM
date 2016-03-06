
#ifndef Building_h
#define Building_h

#include <stdio.h>
#include <stdlib.h>
#include <vector>

class Building{
public:
  // =========================== Constructors ==========================
  Building();
  Building(int length, int width);
  // =========================== Destructor ============================
  ~Building();
  // =========================== Getters ===============================
  inline int length() const;
  inline int width() const;
  
  // =========================== Public Methods ========================
  int whatIsThis();
  std::vector<int> sides(int hole, div_t divresult);
  bool crossing(std::vector<int> v);
  bool merging(std::vector<int> v);
  bool angle90(std::vector<int> v);
  bool corridor(std::vector<int> v);
  
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

#endif /* Building_h */
