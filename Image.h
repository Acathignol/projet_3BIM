
#ifndef IMAGEPPM_H__
#define IMAGEPPM_H__

#include <fstream>
#include <cstring>

using namespace std;

class Image
{
 public :
  // =========================== Constructors ==========================
 
  Image();
  Image( const string& filename );
  Image( const Image& image );
  Image( int** map , int H, int W);

  //=========================== Destructor =============================

  ~Image();

  // =========================== Getters ===============================

  inline int width() const;
  inline int height() const;
  inline int maxVal() const;

  //=========================== Setters ================================

  //=========================== Operators ==============================

  //=========================== Public Methods =========================

  void desaturate();
  void gaussian_blur( double* matrix );
  void save( string filename );
  
protected :
  //=========================== Protected Methods ======================

  //=========================== Attributes =============================

  int W_;
  int H_;
  int MaxVal_;
  unsigned char* data_;
};


inline int Image::height(void) const { return W_; }
inline int Image::width(void) const { return H_; }
inline int Image::maxVal(void) const { return MaxVal_; }

#endif // IMAGEPPM_H__


