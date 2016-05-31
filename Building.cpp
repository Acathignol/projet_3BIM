
#include "Building.h"

//================= Definition of static attributes ====================

int Building::NPEDEST = 150;
int Building::ZOOM = 10;

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
  cout << ")\nnumber of y edges: " << int(yborders_.size()) << " ( ";
  for (unsigned int i=0; i<yborders_.size(); i++){
    cout << yborders_[i];
    cout << " ";
  }
  cout << ")\n";
  
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
}

//=========================== Public Methods ===========================

double Building::getZoneLimNear(unsigned int x, unsigned int y, unsigned int main_dir ){
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

unsigned int Building::getDirection(unsigned int x, unsigned int y){
  //haut = 0
  //droite = 1
  //bas = 2
  //gauche = 3
  int a = x-y; 
  
  return 1*(a!=0 or a==0);
}

void Building::movePeople(void){
  
  for (int i=0; i<Building::NPEDEST; i++){
    int x = people_[i].x();
    int y = people_[i].y();
    if (x>=width_-1 or x<0 or y<0 or y>=length_) continue; //ne bouge plus ceux qui sont sortis
    
    int main_dir = getDirection(x,y);
    double I = people_[i].speed();
    float r = people_[i].radius();
    
    double zone_xmin = 0;
    double zone_ymin = 0;
    double zone_xmax = 0;
    double zone_ymax = 0;
    
    switch (main_dir){
      //la zone à scanner est entre toi et le bord de la zone ou tu vas,
      //et de largeur toi + moitié de radius_max de chaque coté
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
        distance -= (r + obstacles[i].radius())/6;
        if (distance < I ){
          I = distance;
          if (I<0) I=0;
        }
      }
    }
    double x_move = ( (main_dir==1)-(main_dir==3) )*I;
    double y_move = ( (main_dir==2)-(main_dir==0) )*I;
    
    people_[i].move( x_move , y_move , I, Building::ZOOM);
  }
}

vector<Pedest> Building::scanZone(double zone_xmin, double zone_xmax, double zone_ymin, double zone_ymax){
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
  int x;
  int y;
  for (int i=0; i<Building::NPEDEST; i++){
    x = people_[i].x();
    y = people_[i].y();
    if (not (x>=width_-1 or x<0 or y<0 or y>=length_)) return true;
  }
  return false;
}
