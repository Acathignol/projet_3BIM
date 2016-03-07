
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
    if (length_==0){printf ("You are not allowed to use the whatIsThis"
		" method with a length = 0");}
    else{
	  div_t divresult;
      divresult = div (i,length_);
      printf (" %d div by len => %d, remainder %d.\n", i,divresult.quot,
       divresult.rem); // TEST
  
      if (divresult.quot!=0 and divresult.quot !=(length_-1) and 
      divresult.rem!=0 and divresult.rem !=(width_-1) and map_[i]==0){
	    std::vector<int> v = this->sides(i, divresult);
	    if (this->crossing(v)){result = 1 ;} //then put if else once tested if one is never another
	    if (this->merging(v)){result = 2 ;}
	    if (this->angle(v)){result = 3 ;}
	    if (this->corridor(v)){result = 4 ;}
	  }    
	}
  }//Problem : si === : détectera 3 angles plas ...
  return result;
}

std::vector<int> Building::sides(int hole, div_t divresult){
  std::vector<int> vSides;
  
  //0 NORTH
  vSides.push_back(map_[(divresult.quot-1)*length_+divresult.rem]);
  //1 N-W
  vSides.push_back(map_[(divresult.quot-1)*length_+divresult.rem-1]);
  //2 N-E
  vSides.push_back(map_[(divresult.quot-1)*length_+divresult.rem+1]);
  //3 SOUTH
  vSides.push_back(map_[(divresult.quot+1)*length_+divresult.rem]);
  //4 S-W
  vSides.push_back(map_[(divresult.quot+1)*length_+divresult.rem-1]);
  //5 S-E
  vSides.push_back(map_[(divresult.quot+1)*length_+divresult.rem+1]);
  //6 WEST
  vSides.push_back(map_[divresult.quot*length_+divresult.rem-1]);
  //7 EST
  vSides.push_back(map_[divresult.quot*length_+divresult.rem+1]);
  
  return vSides;
}

//101   010
//000   101
//101   010
  
//0 NORTH   1 N-W   2 N-E   3 SOUTH   4 S-W   5 S-E   6 WEST   7 EST 

bool Building::crossing(std::vector<int> v){
  bool a = false;
  
  if (v[0]==0 and v[1]==1 and v[2]==1 and v[3]==0 and
  v[4]==1 and v[5]==1 and v[6]==0 and v[7]==0){a = true;}
  
  else if (v[0]==1 and v[1]==0 and v[2]==0 and v[3]==1 and
  v[4]==0 and v[5]==0 and v[6]==1 and v[7]==1){a = true;}
	  
  return a;	
}

//111 101 101 101  010 011 101 110   110 101 011 101     011 010 010 110 others?
//000 100 000 001  101 100 101 001   001 001 100 100     101 101 101 101
//101 101 111 101  101 011 010 110   101 110 101 011     010 011 110 010

//0 NORTH   1 N-W   2 N-E   3 SOUTH   4 S-W   5 S-E   6 WEST   7 EST

bool Building::merging(std::vector<int> v){
  bool a = false;
  
  //90°c
  if (v[0]==1 and v[1]==1 and v[2]==1 and v[3]==0 and
  v[4]==1 and v[5]==1 and v[6]==0 and v[7]==0){a = true;}
	  
  else if (v[0]==0 and v[1]==1 and v[2]==1 and v[3]==0 and
  v[4]==1 and v[5]==1 and v[6]==1 and v[7]==0){a = true;}
	  
  else if (v[0]==0 and v[1]==1 and v[2]==1 and v[3]==1 and
  v[4]==1 and v[5]==1 and v[6]==0 and v[7]==0){a = true;}

  else if (v[0]==0 and v[1]==1 and v[2]==1 and v[3]==0 and
  v[4]==1 and v[5]==1 and v[6]==0 and v[7]==1){a = true;}
  
  
  else  if (v[0]==1 and v[1]==0 and v[2]==1 and v[3]==1 and
  v[4]==0 and v[5]==0 and v[6]==1 and v[7]==1){a = true;}
  
  else if (v[0]==1 and v[1]==0 and v[2]==0 and v[3]==1 and
  v[4]==0 and v[5]==1 and v[6]==1 and v[7]==1){a = true;}
	  
  else if (v[0]==1 and v[1]==0 and v[2]==0 and v[3]==1 and
  v[4]==1 and v[5]==0 and v[6]==1 and v[7]==1){a = true;}
  
  else if (v[0]==1 and v[1]==1 and v[2]==0 and v[3]==1 and
  v[4]==0 and v[5]==0 and v[6]==1 and v[7]==1){a = true;}
  
  
  //45°c
  else  if (v[0]==1 and v[1]==0 and v[2]==0 and v[3]==0 and
  v[4]==1 and v[5]==1 and v[6]==1 and v[7]==1){a = true;}
  
  else if (v[0]==1 and v[1]==0 and v[2]==1 and v[3]==1 and
  v[4]==0 and v[5]==1 and v[6]==1 and v[7]==0){a = true;}
	  
  else if (v[0]==0 and v[1]==1 and v[2]==1 and v[3]==1 and
  v[4]==0 and v[5]==0 and v[6]==1 and v[7]==1){a = true;}
  
  else if (v[0]==0 and v[1]==1 and v[2]==1 and v[3]==1 and
  v[4]==0 and v[5]==1 and v[6]==1 and v[7]==0){a = true;}
  
  
  else if (v[0]==1 and v[1]==1 and v[2]==0 and v[3]==0 and
  v[4]==1 and v[5]==1 and v[6]==0 and v[7]==1){a = true;}
	  
  else if (v[0]==0 and v[1]==1 and v[2]==1 and v[3]==1 and
  v[4]==1 and v[5]==0 and v[6]==0 and v[7]==1){a = true;}
	  
  else if (v[0]==1 and v[1]==0 and v[2]==1 and v[3]==0 and
  v[4]==1 and v[5]==1 and v[6]==1 and v[7]==0){a = true;}

  else if (v[0]==0 and v[1]==1 and v[2]==1 and v[3]==0 and
  v[4]==1 and v[5]==1 and v[6]==0 and v[7]==1){a = true;}
  
  return a;	
}
 
//111 101 101 111  010 011 111 110  110 011 101 101  111 011 110 111 others?
//001 001 100 100  101 101 101 101  101 101 101 101  100 100 001 001 
//101 111 111 101  111 011 010 110  101 101 011 110  011 111 111 110

//0 NORTH   1 N-W   2 N-E   3 SOUTH   4 S-W   5 S-E   6 WEST   7 EST

bool Building::angle(std::vector<int> v){
  bool a = false;
  
  //90°c
  if (v[0]==1 and v[1]==1 and v[2]==1 and v[3]==0 and
  v[4]==1 and v[5]==1 and v[6]==0 and v[7]==1){a = true;}
    
  else if (v[0]==0 and v[1]==1 and v[2]==1 and v[3]==1 and
  v[4]==1 and v[5]==1 and v[6]==0 and v[7]==1){a = true;}
    
  else if (v[0]==0 and v[1]==1 and v[2]==1 and v[3]==1 and
  v[4]==1 and v[5]==1 and v[6]==1 and v[7]==0){a = true;}
  
  else if (v[0]==1 and v[1]==1 and v[2]==1 and v[3]==0 and
  v[4]==1 and v[5]==1 and v[6]==1 and v[7]==0){a = true;}
  
  
  else  if (v[0]==1 and v[1]==0 and v[2]==0 and v[3]==1 and
  v[4]==1 and v[5]==1 and v[6]==1 and v[7]==1){a = true;}
  
  else if (v[0]==1 and v[1]==0 and v[2]==1 and v[3]==1 and
  v[4]==0 and v[5]==1 and v[6]==1 and v[7]==1){a = true;}
  
  else if (v[0]==1 and v[1]==1 and v[2]==1 and v[3]==1 and
  v[4]==0 and v[5]==0 and v[6]==1 and v[7]==1){a = true;}
  
  else if (v[0]==1 and v[1]==1 and v[2]==0 and v[3]==1 and
  v[4]==1 and v[5]==0 and v[6]==1 and v[7]==1){a = true;}
  
  //45°c
  else  if (v[0]==1 and v[1]==1 and v[2]==0 and v[3]==0 and
  v[4]==1 and v[5]==1 and v[6]==1 and v[7]==1){a = true;}
  
  else if (v[0]==1 and v[1]==0 and v[2]==1 and v[3]==0 and
  v[4]==1 and v[5]==1 and v[6]==1 and v[7]==1){a = true;}
  
  else if (v[0]==0 and v[1]==1 and v[2]==1 and v[3]==1 and
  v[4]==0 and v[5]==1 and v[6]==1 and v[7]==1){a = true;}
  
  else if (v[0]==0 and v[1]==1 and v[2]==1 and v[3]==1 and
  v[4]==1 and v[5]==0 and v[6]==1 and v[7]==1){a = true;}
  
  else if (v[0]==1 and v[1]==1 and v[2]==1 and v[3]==1 and
  v[4]==0 and v[5]==1 and v[6]==1 and v[7]==0){a = true;}
  
  else if (v[0]==1 and v[1]==0 and v[2]==1 and v[3]==1 and
  v[4]==1 and v[5]==1 and v[6]==1 and v[7]==0){a = true;}
  
  else if (v[0]==1 and v[1]==1 and v[2]==0 and v[3]==1 and
  v[4]==1 and v[5]==1 and v[6]==0 and v[7]==1){a = true;}
  
  else if (v[0]==1 and v[1]==1 and v[2]==1 and v[3]==1 and
  v[4]==1 and v[5]==0 and v[6]==0 and v[7]==1){a = true;}
  
  return a;	
}

//101  111  011  110
//101  000  101  101
//101  111  110  011

//0 NORTH   1 N-W   2 N-E   3 SOUTH   4 S-W   5 S-E   6 WEST   7 EST

bool Building::corridor(std::vector<int> v){
  bool a = false;
  
  if (v[0]==0 and v[1]==1 and v[2]==1 and v[3]==0 and
  v[4]==1 and v[5]==1 and v[6]==1 and v[7]==1){a = true;}
  
  else if (v[0]==1 and v[1]==1 and v[2]==1 and v[3]==1 and
  v[4]==1 and v[5]==1 and v[6]==0 and v[7]==0){a = true;}
  
  else if (v[0]==1 and v[1]==0 and v[2]==1 and v[3]==1 and
  v[4]==1 and v[5]==0 and v[6]==1 and v[7]==1){a = true;}
  
  else if (v[0]==1 and v[1]==1 and v[2]==0 and v[3]==1 and
  v[4]==0 and v[5]==1 and v[6]==1 and v[7]==1){a = true;}
	  
  return a;	
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
        if ( i==way[k].x() and j==way[k].y() ) pixel = 'o';
      }
      cout << pixel << " ";
    }   
    cout << endl;
  }
  cout << endl;
}
