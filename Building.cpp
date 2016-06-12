
#include "Building.h"

//================= Definition of static attributes ====================

int Building::NPEDEST = 150;
int Building::ZOOM = 15; //15px = 1m = 1 case de tableau et 1 itération = 1s

//=========================== Constructors =============================

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
  
  cout << filename << " successfully loaded." << endl;
  cout << "Height: " << length_ << endl;
  cout << "Width: " << width_ << endl;
  
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
          RectangleShape wall(Vector2f(Building::ZOOM*(j-1-start),Building::ZOOM));
          wall.setPosition(Building::ZOOM*start, Building::ZOOM*i);
          walls_.push_back( wall );
        }
        state = false;
      }
      else if (state and j==width_-1){
        if (j-start){
          RectangleShape wall(Vector2f(Building::ZOOM*(j-start),Building::ZOOM));
          wall.setPosition(Building::ZOOM*start, Building::ZOOM*i);
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
          RectangleShape wall(Vector2f(Building::ZOOM,Building::ZOOM*(i-start)));
          wall.setPosition(Building::ZOOM*j, Building::ZOOM*start);
          walls_.push_back( wall );
        }
        state = false;
      }
      else if (state and i==length_-1){
        if (i-start){
          RectangleShape wall(Vector2f(Building::ZOOM,Building::ZOOM*(i-start+1)));
          wall.setPosition(Building::ZOOM*j, Building::ZOOM*start);
          walls_.push_back( wall );
        }
        state = false;
      }
    }
  }
  
  //repérage des angles de mur
  
  for (int x=0; x<width_; x++){
    for (int y=0; y<length_; y++){
      vector<int> test;
      int a=0;
      int b=0;
      if (map_[x+y*width_]){
        for (int i=-1; i<=1; i++){
          for (int j=-1; j<=1; j++){
            a=x+i;
            b=y+j;
            if ((i+j)*(i+j)==1){
              if (a>=0 and a<width_ and b>=0 and b<length_){ test.push_back(map_[a+b*width_]); }
              else { test.push_back(9); }
            }
          }
        }
      }
      if (test.size() == 4){
        
        if ( (((test[0]==0 and test[3]!=0) xor (test[0]!=0 and test[3]==0) and
        (test[1]!=1 and test[2]!=1)) xor ((test[1]==0 and test[2]!=0) xor
        (test[1]!=0 and test[2]==0) and (test[0]!=1 and test[3]!=1))) or
        ((test[0]==1 and test[1]==1 and test[2]!=1 and test[3]!=1) or
        (test[3]==1 and test[2]==1 and test[1]!=1 and test[0]!=1) or
        (test[0]==1 and test[2]==1 and test[1]!=1 and test[3]!=1) or
        (test[1]==1 and test[3]==1  and test[0]!=1 and test[2]!=1)) )
        { 
          int countx = 0;
          int county = 0;

          for (int i =0; i<int(xborders_.size()); i++)
          {
            if (xborders_[i]==x) countx++;
          }
          if (countx==0) xborders_.push_back(x);
          for (int i =0; i<int(yborders_.size()); i++)
          {
            if (yborders_[i]==y) county++;
          }
          if (county==0) yborders_.push_back(y);
        }
        
      }
      while (test.size()){test.pop_back();}
    }
  }
  
  cout << "number of x edges: " << int(xborders_.size()) << " ( ";
  for (unsigned int i=0; i<xborders_.size(); i++){
    cout << xborders_[i];
    cout << " ";
  }
  sort(yborders_.begin(), yborders_.end());
  cout << ")\nnumber of y edges: " << int(yborders_.size()) << " ( ";
  for (unsigned int i=0; i<yborders_.size(); i++){
    cout << yborders_[i];
    cout << " ";
  }
  cout << ")\n";
  

  //Création d'objets Zone
  vector<int> xmin_;
  vector<int> xmax_;
  vector<int> ymin_;
  vector<int> ymax_;
  for( unsigned int i=0; i<xborders_.size()-1; i++){
    for( unsigned int j=0; j<yborders_.size()-1; j++){
      xmin_.push_back(xborders_[i]);
      xmax_.push_back(xborders_[i+1]);
      ymin_.push_back(yborders_[j]);
      ymax_.push_back(yborders_[j+1]);
    }
  }
  
  //Création de la grille réduite
  int w = 2*xborders_.size()-1;
  int l = 2*yborders_.size()-1;
  int* nodemap_ = new int[w*l];
  for(int j=0; j<l; j++){
    for(int i=0; i<w; i++){
      nodemap_[ i+w*j ] = 0;
      if (not (i%2)) nodemap_[ i+w*j] = 1;
      if (not (j%2)) nodemap_[ i+w*j] = 1;
    }   
  } 
  for(unsigned int i=0; i<xmin_.size(); i++){
    
    vector<int> directions;
    if (not map_[ymin_[i]*width_+xmin_[i]+1]) directions.push_back(0);
    if (not map_[(1+ymin_[i])*width_+xmax_[i]]) directions.push_back(1);
    if (not map_[(ymax_[i])*width_+xmin_[i]+1]) directions.push_back(2);
    if (not map_[(1+ymin_[i])*width_+xmin_[i]]) directions.push_back(3);
    
    int y = i%(yborders_.size()-1);
    int x = i/int(yborders_.size()-1);
    for(unsigned int j=0; j<directions.size(); j++){
      int a = directions[j];
      if (a==0) nodemap_[(y+1)*2*w+2*x-2*w+1] = 0;
      if (a==1) nodemap_[(y+1)*2*w+2*x-w+2] = 0;
      if (a==2) nodemap_[(y+1)*2*w+2*x+1] = 0;
      if (a==3) nodemap_[(y+1)*2*w+2*x-w] = 0;
    }
  }
  
  //flood sur la grille réduite
  will_tab = new int[w*l];
  for(unsigned int i=0; i<xmin_.size(); i++){
    int Y = i%(yborders_.size()-1);
    int X = i/int(yborders_.size()-1);
    int x = 2*X+1;
    int y = 2*Y+1;
    pair<int, int> start (x,y);
    vector<pair<int, int>> path_to_exit = findExit(start, nodemap_, w, l);
    pair<int, int> a = path_to_exit[0];
    pair<int, int> b = path_to_exit[1];
    int dir = ((b.first-a.first)>0)+3*((b.first-a.first)<0)+2*((b.second-a.second)>0);
    will_tab[Y*(xborders_.size()-1)+X] = dir;
  }
  
  delete[] nodemap_;
  nodemap_ = nullptr;
  
  //Création des piétons
  cout << "placing pedestrians..." << endl;
  int N = Building::NPEDEST;
  people_ = new Pedest[N];
  for (int i=0; i<N; i++){
    unsigned int posX = rand()%width_;
    unsigned int posY = rand()%length_;
    while (this->map(posX, posY)){
      posX = rand()%width_;
      posY = rand()%length_;
    }
    people_[i] = Pedest(posX, posY, Building::ZOOM);
  }
  
  cout << Building::NPEDEST << " pedestrians randomly placed in this floor.\n" << endl;
}

//=========================== Destructor ===============================

Building::~Building(){
  delete[] map_;
  map_ = nullptr;
  delete[] will_tab;
  will_tab = nullptr;
  delete[] people_;
  people_ = nullptr;
}

//=========================== Public Methods ===========================

vector<pair<int, int>> Building::findExit(const pair<int, int>& start, int* map, int W, int H){
  
  // repère tous les points "sortie":
  vector<pair<int, int>> list_of_exits;
  for (int i=0; i<W; i++){
    if (not map[0*W+i]) list_of_exits.push_back( pair<int, int>(i,0) );
    if (not map[(H-1)*W+i]) list_of_exits.push_back( pair<int, int>(i,(H-1)) );
  }
  for (int j=0; j<H; j++){
    if (not map[j*W+0]) list_of_exits.push_back( pair<int, int>(0,j) );
    if (not map[j*W+(W-1)]) list_of_exits.push_back( pair<int, int>((W-1),j) );
  }
  
  vector<pair<int, int>> best_way;
  pair<int, int> coord;
  pair<int, int> coo;
  pair<int, int> stop;
  int k;
  int* grid = nullptr;
  int* flood = nullptr;

  //calcule le chemin pour chaque point possible:
  
  for (size_t i=0; i<list_of_exits.size(); i++){
    
    vector<pair<int, int>> trajectory;
    stop = list_of_exits[i];
    grid = new int [H*W];
    for (int i=0; i<H*W; i++){ grid[i] = -map[i]; }
    grid[ start.first + W*start.second ] = 1;
    grid[ stop.first + W*stop.second ] = 0;
    
    //innondation jusqu'à atteindre stop ou k=20000
    k = 1;
    while ( grid[ stop.first + W*stop.second ]==0 and k<20000){
      flood = new int[H*W];
      for (int i=0; i<W*H; i++){ flood[i] = 0; }
      for (int a=0; a<W; a++){
        for (int b=0; b<H; b++){
          if (grid[a+W*b]>0){
            for (int l=-1; l<2; l++){
              for (int m=-1; m<2; m++){
                if (a+l<W and b+m<H and a+l>=0 and b+m>=0){
                  if (grid[ a+l+W*(b+m) ] != -1 and flood[ a+l+W*(b+m) ] == 0){
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
      flood = nullptr;
      k++;
    }
    
    //remonter les coordonnées jusqu'à start:
    coord = stop;
    int max;
    while ((coord.first!=start.first or coord.second!=start.second) 
           and trajectory.size()<50*(unsigned int) W)
    {
      trajectory.push_back(coord);
      max = 0;
      coo = coord;
      for (int a=-1; a<2; a++){
        for (int b=-1; b<2; b++){
          int i = coo.first + a;
          int j = coo.second + b;
          if (i>=0 and i<W and j>=0 and j<H){
            if ( grid[i+W*j]-(a*b!=0) >= max ){
              max = grid[i+W*j];
              coord = make_pair(i,j);
            }
          }
        }
      }
    }
    
    trajectory.push_back( start);
    reverse( trajectory.begin(), trajectory.end() );
    delete[] grid;
    grid = nullptr;
    
    if ( best_way.size() == 0 or trajectory.size() <= best_way.size()){
      best_way = vector<pair<int, int>>(trajectory);
    }
    
  }
  
  return best_way;
}



double Building::getZoneLimNear(unsigned int x, unsigned int y, unsigned int main_dir ){
  //Renvoie la limite de la zone à scanner pour ce piéton (à retravailler)
  unsigned int xmax = width_;
  unsigned int xmin = 0;
  for (unsigned int i=0; i<xborders_.size(); i++){
    unsigned int xlim = xborders_[i];
    if (xlim>xmin and xlim<x) xmin = xlim;
    if (xlim<xmax and xlim>x) xmax = xlim;
  }
  unsigned int ymax = length_;
  unsigned int ymin = 0;
  for (unsigned int i=0; i<yborders_.size(); i++){
    unsigned int ylim = yborders_[i];
    if (ylim>ymin and ylim<y) ymin = ylim;
    if (ylim<ymax and ylim>y) ymax = ylim;
  }
  switch (main_dir){
    case 0: 
      return (double) ymin;
      break;
    case 1: 
      return (double) xmax;
      break;
    case 2: 
      return (double) ymax;
      break;
    case 3: return (double) xmin;
  }
  return 1;  // ne se produit jamais normalement
}



unsigned int Building::getDirection(int x, int y){
  //Détection de la zone dans laquelle il est
  int k = 0;
  int l = 0;
  for(unsigned int i=1; i<xborders_.size(); i++){
    if (x<xborders_[i]){
      k=i-1;
      break;
    }
  }
  for(unsigned int i=1; i<yborders_.size(); i++){
    if (y<yborders_[i]){
      l=i-1;
      break;
    }
  }
  
  //Renvoie la direction que la volonté du piéton veut prendre
  //haut = 0
  //droite = 1
  //bas = 2
  //gauche = 3S
  return will_tab[l*(xborders_.size()-1)+k];
}



void Building::movePeople(void){
  
  for (int i=0; i<Building::NPEDEST; i++){
    int x = people_[i].x();
    int y = people_[i].y();
    if (x>=width_ or x<0 or y<0 or y>=length_) continue; //ne bouge plus ceux qui sont sortis
    
    int main_dir = getDirection(x,y);
    double I = people_[i].speed();
    float r = people_[i].radius();
    
    double zone_xmin = 0;
    double zone_ymin = 0;
    double zone_xmax = 0;
    double zone_ymax = 0;
    
    switch (main_dir){
      //la zone à scanner est entre toi et le bord de la zone ou
      
      //Rajouter détection des murs ==> Si oui limite de la zone
      // ==> Si non visible jusqu'au prochain mur dans cette direction
      // + détection des murs latéraux.
      case 0: 
        zone_ymax = (double) y;
        zone_ymin = getZoneLimNear(x,y,main_dir);
        zone_xmin = (double) x - r/Building::ZOOM - 6/Building::ZOOM;
        zone_xmax = (double) x + r/Building::ZOOM + 6/Building::ZOOM;
        break;
      case 1:
        zone_xmin = (double) x;
        zone_xmax = getZoneLimNear(x,y,main_dir);
        zone_ymin = (double) y - r/Building::ZOOM - 6/Building::ZOOM;
        zone_ymax = (double) y + r/Building::ZOOM + 6/Building::ZOOM;
        break;
      case 2:
        zone_ymin = (double) y;
        zone_ymax = getZoneLimNear(x,y,main_dir);
        zone_xmin = (double) x - r/Building::ZOOM - 6/Building::ZOOM;
        zone_xmax = (double) x + r/Building::ZOOM + 6/Building::ZOOM;
        break;
      case 3:
        zone_xmax = (double) x;
        zone_xmin = getZoneLimNear(x,y,main_dir);
        zone_ymin = (double) y - r/Building::ZOOM - 6/Building::ZOOM;
        zone_ymax = (double) y + r/Building::ZOOM + 6/Building::ZOOM;
    }
    
    I += (people_[i].eqSpeed()-I)/2;
    
    vector<Pedest> obstacles = scanZone(zone_xmin, zone_xmax, zone_ymin, zone_ymax);
    if ( obstacles.size() ){
      
      for (unsigned int i=0; i<obstacles.size(); i++){
        double distance = (double) sqrt( pow(abs(x-obstacles[i].x()),2) + pow(abs(y-obstacles[i].y()),2) );
        distance -= (r + obstacles[i].radius())/ (double) Building::ZOOM;
        if (distance < I ){
          I = distance;
          if (I<0) I=0;
        }
      }
      
    }
    // terme de volonté + terme d'évitement d'obstacle à rajouter
    double x_move = ( (main_dir==1)-(main_dir==3) )*I;
    double y_move = ( (main_dir==2)-(main_dir==0) )*I;
    // à tester pas de dépassement d'un xlim ou ylim défini par les murs
    
    people_[i].move( x_move , y_move , I, Building::ZOOM);
  }
}



vector<Pedest> Building::scanZone(double zone_xmin, double zone_xmax, double zone_ymin, double zone_ymax){
  // renvoie la liste des piétons dans la zone scannée
  vector<Pedest> obstacles;
  for (int i=0; i<Building::NPEDEST; i++){
    double x = people_[i].x();
    double y = people_[i].y();
    if (zone_xmin<x and x<zone_xmax and zone_ymin<y and y<zone_ymax){
      obstacles.push_back(people_[i]);
    }
  }
  return obstacles;
}



bool Building::notEmpty(void) const{
  // teste si tous les piétons sont sortis ou non
  int x;
  int y;
  for (int i=0; i<Building::NPEDEST; i++){
    x = people_[i].x();
    y = people_[i].y();
    if (not (x>=width_ or x<0 or y<0 or y>=length_)) return true;
  }
  return false;
}

void Building::drawData(int* map, int w, int l) const {
  cout << endl;
  for(int j=0; j<l; j++){
    for(int i=0; i<w; i++){
      cout << map[i+w*j] << " ";
    }   
    cout << endl;
  }
  cout << endl;
}
