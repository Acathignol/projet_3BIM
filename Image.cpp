//===================================Includes===========================

#include "Image.h"

//====================== Definition of static attributes ===============


//===============================Constructors ==========================

Image::Image() {
  W_=0;
  H_=0;
  MaxVal_=255;
  data_ = nullptr;
}

Image::Image( const Image& image ){
  W_      = image.W_;
  H_      = image.H_;
  MaxVal_ = image.MaxVal_;
  data_   = new unsigned char[W_*H_*3];
  memcpy(data_, image.data_, sizeof(unsigned char)*W_*H_*3);
}

Image::Image( const string& filename ) {
  ifstream f( filename.c_str() , ios::in);
  string P6;
  f >> P6 >> W_ >> H_ >> MaxVal_ ;
  f.get();
  data_ = new unsigned char[ W_*H_*3 ];
  f.read((char*)data_ , sizeof(unsigned char)*W_*H_*3);
  f.close();
}

Image::Image( int** map , int H, int W){
  W_ = W;
  H_ = H;
  MaxVal_ = 255;
  data_ = new unsigned char[ W_*H_*3 ];
  for (int i=0; i<W; i++){
    for (int j=0; j<H; j++){
      if (map[i][j]){
        data_[(W*j+i)*3] = (unsigned char) 255;
        data_[(W*j+i)*3+1] = (unsigned char) 0;
        data_[(W*j+i)*3+2] = (unsigned char) 0;
      }
      else {
        data_[(W*j+i)*3] = (unsigned char) 255;
        data_[(W*j+i)*3+1] = (unsigned char) 255;
        data_[(W*j+i)*3+2] = (unsigned char) 255;
      }
    }
  }
}

//=============================== Destructor ===========================

Image::~Image(){
  delete[] data_;
  data_ = nullptr;
}

//=========================== Public Methods ===========================

void Image::save( string filename ){
  fstream f( filename.c_str(), ios::out | ios::trunc | ios::binary);
  f << "P6\n" << W_ << " " << H_ << "\n" << MaxVal_ << "\n";
  f.write((char*)data_ , sizeof(char)*W_*H_*3);
  f.close();
}

void Image::desaturate(){
  for (int x = 0; x < W_; x++)
  {
    for (int y = 0; y < H_; y++)
    {
      double r = (double) data_[(x*H_+y)*3];
      double g = (double) data_[(x*H_+y)*3+1];
      double b = (double) data_[(x*H_+y)*3+2];
      double m = 0.21*r+0.71*g+0.07*b;  
      if (m < 0.0) m = 0.0;
      if (m > MaxVal_) m = (double) MaxVal_;
      
      data_[(x*H_+y)*3]   = (unsigned char) m;
      data_[(x*H_+y)*3+1] = (unsigned char) m;
      data_[(x*H_+y)*3+2] = (unsigned char) m;
    }
  }
}

void Image::gaussian_blur( double* matrix ){
  unsigned char* newdata_ = new unsigned char[W_*H_*3];
  for (int x = 0; x < W_; x++)
  {
    for (int y = 0; y < H_; y++)
    {
      for(int c = 0; c < 3; c++)
      {
        double s   = 0.0;
        double sum = 0.0;
        for (int i = -1; i < 2; i++)
        {
          for(int j = -1; j < 2; j++)
          {
            if (x+i < W_ && x+i >= 0 && y+j < H_ && y+j >= 0)
            {
              s   += (double)data_[((x+i)*H_+(y+j))*3+c]*matrix[(i+1)+3*(j+1)];
              sum += matrix[(i+1)+3*(j+1)];
            }
          }
        }
        s /= sum;
        if (s > 255.0)
        {
          s = 255.0;
        }
        if (s < 0.0)
        {
          s = 0.0;
        }
        newdata_[((x)*H_+(y))*3+c] = (unsigned char)s;
      }
    }
  }
  memcpy(data_, newdata_, sizeof(unsigned char)*W_*H_*3);
  delete[] newdata_;
  newdata_ = nullptr;
}

//=========================== Protected Methods ========================

