
#ifndef IMAGEPPM_H__
#define IMAGEPPM_H__

#include <fstream>
#include <cstring>

using namespace std;

class ImagePPM
{
 public :
  // =========================== Constructors ==========================
 
  ImagePPM();
  ImagePPM( const string& filename );
  ImagePPM( const ImagePPM& image );
  ImagePPM( int** map , int H, int W);

  //=========================== Destructor =============================

  ~ImagePPM();

  // =========================== Getters ===============================

  inline int width() const;
  inline int height() const;
  inline int maxVal() const;
  inline bool getPixel(size_t x, size_t y) const;

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


inline int ImagePPM::height(void) const { return W_; }
inline int ImagePPM::width(void) const { return H_; }
inline int ImagePPM::maxVal(void) const { return MaxVal_; }
inline bool ImagePPM::getPixel(size_t x, size_t y) const {
  return (data_[(W_*y+x)*3]+data_[(W_*y+x)*3+1]+data_[(W_*y+x)*3+2])/3 == 0;
}

#endif // IMAGEPPM_H__


