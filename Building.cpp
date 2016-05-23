
#include "Building.h"

//=========================== Constructors =============================

Building::Building(){
  length_ = 0;
  width_ = 0;
  map_ = nullptr;
}

Building::Building(const string& filename){
  //Ouverture de l'image:
  Image Level;
  if (!Level.loadFromFile(filename))
    exit(-1);
  
  const Uint8* map = Level.getPixelsPtr();
  
  //Construction de map_ :
  Vector2u size = Level.getSize();
  length_ = size.y;
  width_ = size.x;
  map_ = new int[length_*width_];
  for (int i=0; i<length_; i++){
    for (int j=0; j<width_; j++){
      int r = map[j*4 + size.x*4*i];
      map_[j+width_*i] = 1-r%254;
    }
  }
  
    
  //test des murs horizontaux:
  for (int i=0; i<length_; i++){
    unsigned int start = 0;
    bool state = false;
    for (int j=0; j<width_; j++){
      if (map_[j+width_*i] and not state){
        start = j;
        state = true;
      }
      if (state and not map_[j+width_*i]){
        if (j-1-start){
          RectangleShape wall(Vector2f(10*(j-1-start),10));
          wall.setPosition(10*start, 10*i);
          walls_.push_back( wall );
        }
        state = false;
      }
      else if (state and j==width_-1){
        if (j-start){
          RectangleShape wall(Vector2f(10*(j-start),10));
          wall.setPosition(10*start, 10*i);
          walls_.push_back( wall );
        }
        state = false;
      }
    }
  }
  
  //test des murs verticaux:
  for (int j=0; j<width_; j++){
    unsigned int start = 0;
    bool state = false;
    for (int i=0; i<length_; i++){
      if (map_[j+width_*i] and not state){
        start = i;
        state = true;
      }
      if (state and not map_[j+width_*i]){
        if (i-1-start){
          RectangleShape wall(Vector2f(10,10*(i-start)));
          wall.setPosition(10*j, 10*start);
          walls_.push_back( wall );
        }
        state = false;
      }
      else if (state and i==length_-1){
        if (i-start){
          RectangleShape wall(Vector2f(10,10*(i-start+1)));
          wall.setPosition(10*j, 10*start);
          walls_.push_back( wall );
        }
        state = false;
      }
    }
  }
}

//=========================== Destructor ===============================

Building::~Building(){
  delete[] map_;
  map_ = nullptr;
}

//=========================== Public Methods =========================== 
      
std::vector<int> Building::vectorEdges(){
  std::vector<int> result;      
  std::vector<int> test;
  
  for (int x=0; x<width_; x++){
    for (int y=0; y<length_; y++){

      test=testLine(x,y);
      
      if (test.size() != 0){
        result=testAnswer(x,y,test,result);
      }
      while (test.size() != 0){test.pop_back();}
	  }
  }
  return result;
}

std::vector<int> Building::testLine(int x, int y){
  std::vector<int> test;
  int a=0;
  int b=0;
  if (map_[x+y*width_]==1){
    for (int i=-1; i<=1; i++){
      for (int j=-1; j<=1; j++){// CAREFULL HERE I AM NOT TAKING N-E N-W S-E S-W
        a=x+i;
        b=y+j;
        if (checkSides(a,b)){
          if (i==-1 and j==0){ // West
            test.push_back(map_[a+b*width_]);
          }
          else if (i==0 and j==-1){ // South
            test.push_back(map_[a+b*width_]);
          }
          else if (i==0 and j==1){ // North
            test.push_back(map_[a+b*width_]);
          }
          else if (i==1 and j==0){ // Est
            test.push_back(map_[a+b*width_]);
          }
        }
        else{
          if (i==-1 and j==0){ // West
            test.push_back(9);
          }
          else if (i==0 and j==-1){ // South
            test.push_back(9);
          }
          else if (i==0 and j==1){ // North
            test.push_back(9);
          }
          else if (i==1 and j==0){ // Est
            test.push_back(9);
          }
        }
      }
    }
  }
  return test;
}

bool Building::checkSides(int x , int y){
  if (x>=0 and x<width_ and y>=0 and y<length_){return true;}  
  else {return false;}
}

std::vector<int> Building::testAnswer(int x, int y , std::vector<int> test, std::vector<int> result){
  if (test.size() == 4){
    if (((test[0]==0 and test[3]!=0) xor (test[0]!=0 and test[3]==0) and
     (test[1]!=1 and test[2]!=1)) xor ((test[1]==0 and test[2]!=0) xor
      (test[1]!=0 and test[2]==0) and (test[0]!=1 and test[3]!=1))){ 
	  int count = 0 ;
      for (int i =0; i<int(result.size()); i++){
        if (result[i]==x+y*width_){
		  count++;
		}
	  }
      if (count==0){
		result.push_back(x+y*width_);
      }
    }
    else if ((test[0]==1 and test[1]==1 and test[2]!=1 and test[3]!=1) or
     (test[3]==1 and test[2]==1 and test[1]!=1 and test[0]!=1) or
     (test[0]==1 and test[2]==1 and test[1]!=1 and test[3]!=1) or
     (test[1]==1 and test[3]==1  and test[0]!=1 and test[2]!=1)){ 
	  int count = 0 ;
	  if (not (x==0 and y==0) xor (x==width_-1 and y==0) xor 
	  (x==0 and y==length_-1) xor (x==width_-1 and y==length_-1)){
        for (int i =0; i<int(result.size()); i++){
          if (result[i]==x+y*width_){
		    count++;
	  	  }
	    }
        if (count==0){
		  result.push_back(x+y*width_);
        }
      }
    }
  }
  return result;
}

void Building::drawMap(void) const {
  cout << endl;
  for(int j=0; j<length_; j++){
    for(int i=0; i<width_; i++){
      char pixel = ' ';
      if (map_[ i+width_*j] ==1 ) {pixel = '#';}
      cout << pixel << " ";
     
    }   
    cout << endl;
  }
  cout << endl;
}

void Building::drawTrajectory(vector<pair<int, int>> way) const {
  cout << endl;
  for(int j=0; j<length_; j++){
    for(int i=0; i<width_; i++){
      char pixel = ' ';
      if (map_[ i+width_*j] ==1 ) pixel = '#';
      for (size_t k=0; k<way.size(); k++){
        if ( i==way[k].first and j==way[k].second ) pixel = '.';
      }
      cout << pixel << " ";
    }   
    cout << endl;
  }
  cout << endl;
}
