
#include "Building.h"

//=========================== Constructors =============================

Building::Building(){
  length_ = 0;
  width_ = 0;
  map_ = nullptr;
}

Building::Building(int length, int width){
  length_ = length;
  width_ = width;
  map_ = new int[length_*width_];
}

Building::Building(const Image& model){
  length_ = model.height();
  width_ = model.width();
  map_ = new int[length_*width_];
  
  for(int i=0; i<width_; i++){
    for(int j=0; j<length_; j++){
      map_[ j*width_ + i ] = model.getPixel(i,j);
      // black = 1
      // other (for example, white, or red) = 0
    }
  }
}

//=========================== Destructor ===============================

Building::~Building(){
  delete[] map_;
  map_ = nullptr;
}

//=========================== Public Methods ===========================

//Annie (Etudiant 3) : Classe Building : Faire des méthodes pour qu'on puisse dire si un obstacle est un croisement, un virage, une fusion de deux couloirs .....  Afin d'y appliquer les bonnes méthodes de la classe Pedest (et en fonction de leurs humeurs)
//VIRAGE COMPLEX => dire la courbure  ATTENTION ! pas au bordure idem croisement and angle
	    
      
      //~ if (this->crossing(v)){result = 1 ;} //then put if else once tested if one is never another
	    //~ if (this->merging(v)){result = 2 ;}
	    //~ if (this->angle(v)){result = 3 ;}
	    //~ if (this->corridor(v)){result = 4 ;}
      
      
int Building::whatIsThis(){
  int result = 0;//0=nothing, 1=crossing, 2=merging, 3=angle, 4=corridor
  int** copyMap=new int*[width_];
  fillCopyMap(copyMap);
  for (int x=0; x<width_; x++){
    for (int y=0; y<length_; y++){
      //blablabla
      result++;
      
    }
  }
  
  for (int i=0; i<width_; i++){
    delete[] copyMap[i];
  }
  delete[] copyMap;
  copyMap = nullptr;
  
  return result;
}

void Building::fillCopyMap(int** copyMap){
  std::vector<int> test;
  for (int x=0; x<width_; x++){
    copyMap[x]=new int[length_];
    for (int y=0; y<length_; y++){
      copyMap[x][y]=map_[x+y*width_];
      test=testLine(x,y);
      if (test.size() != 0){
        testAnswer(x,y,test,copyMap);
      }
      while (test.size() != 0){test.pop_back();}
	  }
  }
}

std::vector<int> Building::testLine(int x, int y){
  std::vector<int> test;
  int a=0;
  int b=0;
  if (map_[x+y*width_]==1){
    for (int i=-1; i<=1; i++){
      for (int j=-1; j<=1; j++){// CAREFULL HERE I AM ALSO TAKING N-E N-W S-E S-W
        a=x+i;
        b=y+j;
        if (checkSides(a,b)){
          if (i==-1 and j==0){ // West
            numbers.push_back(map_[a+b*width_]);
          }
          else if (i==1 and j==0){ // Est
            numbers.push_back(map_[a+b*width_]);
          }
          else if (i==0 and j==1){ // North
            numbers.push_back(map_[a+b*width_]);
          }
          else if (i==0 and j==-1){ // South
            numbers.push_back(map_[a+b*width_]);
          }
        }
      }
    }
  }
  return test;
}

bool Building::checkSides(int x , int y){
  if (x>=0 && x<width_ and y>=0 && y<length_){return true;}  
  else {return false;}
}

void Building::testAnswer(int x, int y , std::vector<int> test, int** copyMap){
 copyMap[x][y]=1;
}

void Building::drawMap(void) const {
  cout << endl;
  for(int j=0; j<length_; j++){
    for(int i=0; i<width_; i++){
      char pixel = ' ';
      if (map_[ i+width_*j] ==1 ) pixel = '#';
      cout << pixel << " ";
    }   
    cout << endl;
  }
  cout << endl;
}

void Building::drawTrajectory(vector<Point> way) const {
  cout << endl;
  for(int j=0; j<length_; j++){
    for(int i=0; i<width_; i++){
      char pixel = ' ';
      if (map_[ i+width_*j] ==1 ) pixel = '#';
      for (size_t k=0; k<way.size(); k++){
        if ( i==way[k].x() and j==way[k].y() ) pixel = '.';
      }
      cout << pixel << " ";
    }   
    cout << endl;
  }
  cout << endl;
}
