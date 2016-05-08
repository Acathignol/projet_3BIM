
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

Building::Building(const string& filename){
  Image Level;
  if (!Level.loadFromFile(filename))
    exit(-1);
  
  const Uint8* map = Level.getPixelsPtr();
  
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
  //New map 
  int** copyMap=new int*[width_];
  //Filling the map 
  fillCopyMap(copyMap);
  for (int x=0; x<width_; x++){
    for (int y=0; y<length_; y++){
      //Depending on how the map is filled , we obtain different results (angle, corridor...)
      //To do the Maze solver stuf
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
      copyMap[x][y]=0;
      cout<<"bouh1"<<endl;
      test=testLine(x,y);
      if (test.size() != 0){
        
        cout<<test.size()<<endl;
        //~ testAnswer(x,y,test,copyMap);
      }
      cout<<"ko3"<<endl;
      while (test.size() != 0){test.pop_back();}
    }
  }
  drawMap();
  cout<<endl;
  cout<<endl;
  for (int x=0; x<width_; x++){
    for (int y=0; y<length_; y++){
      if (copyMap[x][y]==1){
        cout<<"#";
      }
      else{cout<<" ";}
    }
    cout<<endl;
  }
  cout<<endl;
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
            test.push_back(map_[a+b*width_]);
          }
          else if (i==1 and j==0){ // Est
            test.push_back(map_[a+b*width_]);
          }
          else if (i==0 and j==1){ // North
            test.push_back(map_[a+b*width_]);
          }
          else if (i==0 and j==-1){ // South
            test.push_back(map_[a+b*width_]);
          }
        }
        else{
          if (i==-1 and j==0){ // West
            test.push_back(9);
          }
          else if (i==1 and j==0){ // Est
            test.push_back(9);
          }
          else if (i==0 and j==1){ // North
            test.push_back(9);
          }
          else if (i==0 and j==-1){ // South
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

void Building::testAnswer(int x, int y , std::vector<int> test, int** copyMap){
  if (test.size() == 4){ // CAREFULL I AM NOT TESTING THE BORDERS, AM I?
    if (test[0]==0){                           // A OPTIMISER
      for (int i=0; i<width_; i++){
        copyMap[x][i]=1;
      }
      //~ if (test[1]==0){
        //~ for (int j=0; j<length_; j++){
          //~ copyMap[x][j]=1;
        //~ }
      //~ }
    }
    
    //~ if (test[2]==0){                           // A OPTIMISER
      //~ for (int j=0; j<length_; j++){
        //~ copyMap[x][j]=1;
      //~ }
      //~ if (test[3]==0){
        //~ for (int i=0; i<width_; i++){
          //~ copyMap[i][y]=1;
        //~ }
      //~ }
    //~ }
      
    //~ if (test[0]==1){                           // A OPTIMISER
      //~ for (int i=0; i<width_; i++){
        //~ copyMap[i][y]=1;
      //~ }
      //~ if (test[1]==0){
        //~ for (int j=0; j<length_; j++){
          //~ copyMap[x][j]=1;
          //~ cout<<"DE ";
        //~ }
      //~ }
    //~ }
    //~ else if (test[0]==0 and test[1]==1){
      //~ for (int i=0; i<width_; i++){
        //~ copyMap[i][y]=1;
        //~ cout<<"Bique !"<<endl;
      //~ }
      //~ for (int j=0; j<length_; j++){
        //~ copyMap[x][j]=1;
        //~ 
      //~ }
    //~ }
    //~ else if (test[0]==0 and test[1]==0){
      //~ for (int i=0; i<width_; i++){
        //~ copyMap[i][y]=1;
      //~ }
      //~ for (int j=0; j<length_; j++){
        //~ copyMap[x][j]=1;
      //~ }
    //~ }
    //~ 
    //~ if (test[2]==1){
      //~ for (int j=0; j<length_; j++){
        //~ copyMap[x][j]=1;
        //~ cout<<"méchant ";
      //~ }
      //~ if (test[3]==0){
        //~ for (int i=0; i<width_; i++){
          //~ copyMap[i][y]=1;
          //~ cout<<"bonhomme !"<<endl;
        //~ }
      //~ }
    //~ }
    //~ else if (test[2]==0 and test[3]==1){
      //~ for (int i=0; i<width_; i++){
        //~ copyMap[i][y]=1;
      //~ }
      //~ for (int j=0; j<length_; j++){
        //~ copyMap[x][j]=1;
      //~ }
    //~ }
    //~ else if (test[2]==0 and test[3]==0){
      //~ for (int i=0; i<width_; i++){
        //~ copyMap[i][y]=1;
      //~ }
      //~ for (int j=0; j<length_; j++){
        //~ copyMap[x][j]=1;
      //~ }
    //~ }
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
