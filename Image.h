
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
  int width();
  int height();
  int maxVal();
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

#endif // IMAGEPPM_H__


