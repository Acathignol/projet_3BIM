
#ifndef Building_hpp
#define Building_hpp

#include <stdio.h>

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

#endif /* Building_hpp */
