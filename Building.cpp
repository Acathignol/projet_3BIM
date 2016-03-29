
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

int Building::whatIsThis(){
  int result = 0;//0=nothing, 1=crossing, 2=merging, 3=angle, 4=corridor
  
  for (int i=0; i<(length_*width_); i++){
    for (int j=0; j<(length_*width_); j++){
      
      
	    if (this->crossing(v)){result = 1 ;} //then put if else once tested if one is never another
	    if (this->merging(v)){result = 2 ;}
	    if (this->angle(v)){result = 3 ;}
	    if (this->corridor(v)){result = 4 ;}
	    
	}
  }//Problem : si === : détectera 3 angles plas ...
  return result;
}

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
