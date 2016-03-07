
//=========================== Includes =================================
#include "Pedest.h"

using namespace std;

//================= Definition of static attributes ====================


//=========================== Constructors =============================

Pedest::Pedest() {
  x_ = 0;
  y_ = 0;
  radius_ = 0;
  xp_ = 1.0;
  yp_ = 1.0;
  xpp_ = 0.0;
  ypp_ = 0.0;
  mood_ = 0;
  path_to_exit_ = nullptr;
}

Pedest::Pedest(const int startX, const int startY,const float radius,
               const int* map, const int W, const int H){
  x_ = startX;
  y_ = startY;
  radius_ = radius;
  xp_ = 0.0;
  yp_ = 0.0;
  xpp_ = 0.0;
  ypp_ = 0.0;
  mood_ = 0;
  path_to_exit_ = new vector<Point> (findExit( Point(startX, startY), 
                                               map, W, H));
}

//=========================== Destructor ===============================

Pedest::~Pedest(void){
  delete path_to_exit_;
}

//=========================== Public Methods ===========================


void Pedest::xpp(const double new_xpp){
  xpp_ = new_xpp;
}

void Pedest::ypp(const double new_ypp){
  ypp_ = new_ypp;
}

void Pedest::set_mood(const int new_mood){
  mood_ = new_mood;
}

void Pedest::move(){
  x_ += xp_;
  y_ += yp_;
}

void Pedest::accelerate(){
  if (xpp_ == 0) xpp_ = 0.75;
  if (ypp_ == 0) ypp_ = 0.75;
  xpp_ *= 1.5;
  ypp_ *= 1.5;
  xp_ += xpp_;
  yp_ += ypp_;
}

void Pedest::brake(){
  xp_ -= xpp_;
  yp_ -= ypp_;
  xpp_ = xpp_ /1.5;
  ypp_ = ypp_ /1.5;
  if (xpp_ < 0.1) xpp_ = 0;
  if (ypp_ < 0.1) ypp_ = 0;
}

vector<Point> Pedest::findExit(const Point& start, const int* map, int W, int H){
  // repère tous les points "sortie":
  vector<Point> list_of_exits;
  for (int i=0; i<W; i++){
    if (not map[0*W+i]) list_of_exits.push_back( Point(i,0) );
    if (not map[(H-1)*W+i]) list_of_exits.push_back( Point(i,(H-1)) );
  }
  for (int j=0; j<H; j++){
    if (not map[j*W+0]) list_of_exits.push_back( Point(0,j) );
    if (not map[j*W+(W-1)]) list_of_exits.push_back( Point((W-1),j) );
  }
  
  cout << "List of exits:" << endl;
  for (size_t i=0; i<list_of_exits.size(); i++){
    list_of_exits[i].display();
  }
  
  vector<Point> best_way;
  for (size_t i=0; i<list_of_exits.size(); i++){
    
    //calcule le chemin pour chaque point possible:
    Point stop = list_of_exits[i];
    
    int* grid = new int [H*W];
    for (int i=0; i<H*W; i++){ grid[i] = -map[i]; }
    grid[ start.coord_in(W) ] = 1;
    grid[ stop.coord_in(W) ] = 0;
    
    //innondation jusqu'à atteindre stop ou k=20000
    int k = 1;
    while ( grid[ stop.coord_in(W) ]==0 and k<20000){
      int* flood = new int[H*W];
      for (int i=0; i<W*H; i++){ flood[i] = 0; }
      for (int a=0; a<W; a++){
        for (int b=0; b<H; b++){
          if (grid[a+W*b]>0){
            for (int l=-1; l<2; l++){
              for (int m=-1; m<2; m++){
                if (a+l<W and b+m<H and a+l>=0 and b+m>=0){
                  if (l*m==0 and grid[ a+l+W*(b+m) ] != -1 and flood[ a+l+W*(b+m) ] == 0){
                    flood[ a+l+W*(b+m) ] ++;
                  }
                } 
              }
            }
          }
        }
      }
      
      for (int i=0; i<W*H; i++){ grid[i] += flood[i]; }
      delete[] flood;
      k++;
    }
    
    //remonter les coordonnées jusqu'à start:
    Point coord = stop;
    vector<Point> trajectory;
    Point coo;
    while (coord.x()!=start.x() and coord.y()!=start.y() 
           and trajectory.size()<50*(unsigned int) W)
    {
      trajectory.push_back(coord);
      int max = 0;
      coo = coord;
      for (int a=-1; a<2; a++){
        for (int b=-1; b<2; b++){
          int i = coo.x() + a;
          int j = coo.y() + b;
          if (a*b==0 and i>=0 and i<W and j>=0 and j<H){
            if ( grid[i+W*j] > max ){
              max = grid[i+W*j];
              coord.set(i,j);
            }
          }
        }
      }
    }
    
    reverse( trajectory.begin(), trajectory.end() );
    delete[] grid;
    
    if ( best_way.size() == 0 or trajectory.size() < best_way.size()){
      best_way = trajectory;
    }
  }
  
  return best_way;
}

//=========================== Protected Methods ========================

//=========================== Functions ================================
