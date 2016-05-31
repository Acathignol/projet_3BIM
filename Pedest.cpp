
//=========================== Includes =================================
#include "Pedest.h"

using namespace std;

//================= Definition of static attributes ====================


//=========================== Constructors =============================

Pedest::Pedest() {
  x_ = 0;
  y_ = 0;
  radius_ = 0;
  mood_ = 0;
  img_ = CircleShape();
  speed_ = 0;
  eq_speed_ = 0;
}

Pedest::Pedest(const int startX, const int startY){
  x_ = startX;
  y_ = startY;
  unsigned int r = rand()%3+3;
  radius_ = (float) r;
  mood_ = 0;
  img_ = CircleShape(r);
  img_.setPosition(10*x_, 10*y_);
  img_.setFillColor(Color(Color::Green));
  speed_ = 0;
  eq_speed_ = 0.1*( (double) (rand()%9+1) );
}

Pedest::Pedest(const Pedest& model){
  x_ = model.x_;
  y_ = model.y_;
  radius_ = model.radius_;
  mood_ = model.mood_;
  img_ = model.img_;
  speed_ = model.speed_;
  eq_speed_ = model.eq_speed_;
}

void Pedest::operator=(const Pedest& model){
  x_ = model.x_;
  y_ = model.y_;
  radius_ = model.radius_;
  mood_ = model.mood_;
  img_ = model.img_;
  speed_ = model.speed_;
  eq_speed_ = model.eq_speed_;
}

//=========================== Destructor ===============================

Pedest::~Pedest(void){
}

//=========================== Public Methods ===========================

//~ vector<pair<int, int>> Pedest::findExit(const pair<int, int>& start, const int* map, int W, int H){
  //~ 
  //~ // repère tous les points "sortie":
  //~ vector<pair<int, int>> list_of_exits;
  //~ for (int i=0; i<W; i++){
    //~ if (not map[0*W+i]) list_of_exits.push_back( pair<int, int>(i,0) );
    //~ if (not map[(H-1)*W+i]) list_of_exits.push_back( pair<int, int>(i,(H-1)) );
  //~ }
  //~ for (int j=0; j<H; j++){
    //~ if (not map[j*W+0]) list_of_exits.push_back( pair<int, int>(0,j) );
    //~ if (not map[j*W+(W-1)]) list_of_exits.push_back( pair<int, int>((W-1),j) );
  //~ }
  //~ 
  //~ vector<pair<int, int>> best_way;
  //~ pair<int, int> coord;
  //~ pair<int, int> coo;
  //~ pair<int, int> stop;
  //~ int k;
  //~ int* grid = nullptr;
  //~ int* flood = nullptr;
//~ 
  //~ //calcule le chemin pour chaque point possible:
  //~ 
  //~ for (size_t i=0; i<list_of_exits.size(); i++){
    //~ 
    //~ vector<pair<int, int>> trajectory;
    //~ stop = list_of_exits[i];
    //~ grid = new int [H*W];
    //~ for (int i=0; i<H*W; i++){ grid[i] = -map[i]; }
    //~ grid[ start.first + W*start.second ] = 1;
    //~ grid[ stop.first + W*stop.second ] = 0;
    //~ 
    //~ //innondation jusqu'à atteindre stop ou k=20000
    //~ k = 1;
    //~ while ( grid[ stop.first + W*stop.second ]==0 and k<20000){
      //~ flood = new int[H*W];
      //~ for (int i=0; i<W*H; i++){ flood[i] = 0; }
      //~ for (int a=0; a<W; a++){
        //~ for (int b=0; b<H; b++){
          //~ if (grid[a+W*b]>0){
            //~ for (int l=-1; l<2; l++){
              //~ for (int m=-1; m<2; m++){
                //~ if (a+l<W and b+m<H and a+l>=0 and b+m>=0){
                  //~ if (grid[ a+l+W*(b+m) ] != -1 and flood[ a+l+W*(b+m) ] == 0){
                    //~ flood[ a+l+W*(b+m) ] ++;
                  //~ }
                //~ } 
              //~ }
            //~ }
          //~ }
        //~ }
      //~ }
      //~ 
      //~ for (int i=0; i<W*H; i++){ grid[i] += flood[i]; }
      //~ delete[] flood;
      //~ flood = nullptr;
      //~ k++;
    //~ }
    //~ 
    //~ //remonter les coordonnées jusqu'à start:
    //~ coord = stop;
    //~ int max;
    //~ while ((coord.first!=start.first or coord.second!=start.second) 
           //~ and trajectory.size()<50*(unsigned int) W)
    //~ {
      //~ trajectory.push_back(coord);
      //~ max = 0;
      //~ coo = coord;
      //~ for (int a=-1; a<2; a++){
        //~ for (int b=-1; b<2; b++){
          //~ int i = coo.first + a;
          //~ int j = coo.second + b;
          //~ if (i>=0 and i<W and j>=0 and j<H){
            //~ if ( grid[i+W*j]-0.2*(a*b!=0) >= max ){
              //~ // ce 0.2 autorise les déplacements en diagonale, mais
              //~ // privilégie ceux en ligne droite du coup ! ;)
              //~ max = grid[i+W*j];
              //~ coord = make_pair(i,j);
            //~ }
          //~ }
        //~ }
      //~ }
    //~ }
    //~ 
    //~ reverse( trajectory.begin(), trajectory.end() );
    //~ delete[] grid;
    //~ grid = nullptr;
    //~ 
    //~ if ( best_way.size() == 0 or trajectory.size() <= best_way.size()){
      //~ best_way = vector<pair<int, int>>(trajectory);
    //~ }
    //~ 
  //~ }
  //~ 
  //~ return best_way;
//~ }

void Pedest::move(double x_move , double y_move , double new_speed){
  x_ += x_move;
  y_ += y_move;
  img_.setPosition(10*x_, 10*y_);
  speed_ = new_speed;
}

//=========================== Functions ================================

