
#include "Building.h"

//================= Definition of static attributes ====================

int Building::NPEDEST = 10;
int Building::ZOOM = 15; //15px = 1m = 1 case de tableau et 1 itération = 1s


//=========================== Constructors =============================

Building::Building(const string& filename){
  //...............................................Ouverture de l'image:
  Image Level;
  if (!Level.loadFromFile(filename))
    exit(-1);
  
  const Uint8* map = Level.getPixelsPtr();
  
  //..............................................Construction de map_ :
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
  
  //.............................................. recherche des murs :
  unsigned int start = 0;
  bool state = false;
  for (int i=0; i<length_; i++){//horizontaux
    for (int j=0; j<width_; j++){
      if (map_[j+width_*i] and not state){
        start = j;
        state = true;
      }
      if (state and (not map_[j+width_*i] or j==width_-1)){
        if (j-1-start){
          RectangleShape wall(Vector2f(Building::ZOOM*(j-start+(j==width_-1)),Building::ZOOM));
          wall.setPosition(Building::ZOOM*start, Building::ZOOM*i);
          walls_.push_back( wall );
        }
        state = false;
      }
    }
  }
  for (int j=0; j<width_; j++){
    for (int i=0; i<length_; i++){
      if (map_[j+width_*i] and not state){
        start = i;
        state = true;
      }
      if (state and (not map_[j+width_*i] or i==length_-1)){
        if (i-1-start){
          RectangleShape wall(Vector2f(Building::ZOOM,Building::ZOOM*(i-start+(i==length_-1))));
          wall.setPosition(Building::ZOOM*j, Building::ZOOM*start);
          walls_.push_back( wall );
        }
        state = false;
      }
    }
  }
  
  //..........................................repérage des angles de mur
  
  int s;
  xborders_.push_back(0.5);
  yborders_.push_back(0.5);
  for (int x=0; x<width_; x++){
    for (int y=0; y<length_; y++){
      s = 0;
      for (int i=-1; i<=1; i++){
        for (int j=-1; j<=1; j++){
          if (x+i<0 or y+j<0 or x+i==width_ or y+j==length_) continue;
          if (map_[y*width_+x] and (i+j)*(i+j)==1) s += map_[(y+j)*width_+x+i];
        }
      }
      if ( s>0 and s!=2){
        if(find(xborders_.begin(),xborders_.end(),x+0.5)==xborders_.end()) xborders_.push_back(x+0.5);
        if(find(yborders_.begin(),yborders_.end(),y+0.5)==yborders_.end()) yborders_.push_back(y+0.5);
      }
    }
  }
  
  cout << "number of x edges: " << int(xborders_.size()) << " ( ";
  for (unsigned int i=0; i<xborders_.size(); i++){
    RectangleShape wall(Vector2f(1,Building::ZOOM*length_));
    wall.setPosition(Building::ZOOM*xborders_[i], 0);
    wall.setFillColor(Color::Red);
    walls_.push_back( wall );
    cout << xborders_[i];
    cout << " ";
  }
  sort(yborders_.begin(), yborders_.end());
  cout << ") mètres\nnumber of y edges: " << int(yborders_.size()) << " ( ";
  for (unsigned int i=0; i<yborders_.size(); i++){
    RectangleShape wall(Vector2f(Building::ZOOM*width_,1));
    wall.setPosition(0,Building::ZOOM*yborders_[i]);
    wall.setFillColor(Color::Red);
    walls_.push_back( wall );
    cout << yborders_[i];
    cout << " ";
  }
  cout << ") mètres\n";

  //......................................... Recherche de la sortie :
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
    //~ cout<<"zone: "<<xmin_[i]<<','<<xmax_[i]<<','<<ymin_[i]<<','<<ymax_[i]<<" : ";
    if (not map_[ymin_[i]*width_+xmin_[i]+1]) directions.push_back(0);
    if (not map_[(1+ymin_[i])*width_+xmax_[i]]) directions.push_back(1);
    if (not map_[(ymax_[i])*width_+xmin_[i]+1]) directions.push_back(2);
    if (not map_[(1+ymin_[i])*width_+xmin_[i]]) directions.push_back(3);
    int y = i%(yborders_.size()-1);
    int x = i/int(yborders_.size()-1);
    for(unsigned int j=0; j<directions.size(); j++){
      int a = directions[j];
      //~ cout<<a<<" - ";
      if (a==0) nodemap_[(y+1)*2*w+2*x-2*w+1] = 0;
      if (a==1) nodemap_[(y+1)*2*w+2*x-w+2] = 0;
      if (a==2) nodemap_[(y+1)*2*w+2*x+1] = 0;
      if (a==3) nodemap_[(y+1)*2*w+2*x-w] = 0;
    }
    //~ cout<<endl;
  }
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
  this->drawData( will_tab, xborders_.size()-1, yborders_.size()-1);
  //~ this->drawMap( map_, width_, length_);
  delete[] nodemap_;
  nodemap_ = nullptr;

  //..............................................Création des piétons :
  cout << "placing pedestrians..." << endl;
  int N = Building::NPEDEST;
  people_ = new Pedest[N];
  for (int i=0; i<N; i++){
    unsigned int posX = rand()%width_;
    unsigned int posY = rand()%length_;
    //~ unsigned int posX = 2;
    //~ unsigned int posY = 2;
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

unsigned int Building::getDirection(double x, double y){
  //Détection de la zone dans laquelle il est
  int k = 0;
  int l = 0;
  for(unsigned int i=1; i<xborders_.size(); i++){
    if (x<xborders_[i]){
      k=i-1;
      break;
    }
    else { k=xborders_.size()-2; }
  }
  for(unsigned int i=1; i<yborders_.size(); i++){
    if (y<yborders_[i]){
      l=i-1;
      break;
    }
    else { l=yborders_.size()-2; }
  }
  
  //Renvoie la direction que la volonté du piéton veut prendre
  //haut = 0
  //droite = 1
  //bas = 2
  //gauche = 3
  
  //~ cout << l << ',' << k << ": ";
  //~ cout << "x=" << x << " y=" << y << " - ";
  //~ cout << will_tab[l*(xborders_.size()-1)+k] << endl;
  return will_tab[l*(xborders_.size()-1)+k];

}

void Building::movePeople(void){
  
  for (int i=0; i<Building::NPEDEST; i++){
    double x = people_[i].x();
    double y = people_[i].y();
    if (x>width_+2 or x<0 or y<0 or y>length_+2) continue; //ne bouge plus ceux qui sont sortis
    double I = people_[i].speed();
    float r = people_[i].radius();
    
    // =============== Détermintion de la volonté ======================
    
    int main_dir = getDirection(x,y);
    I += (people_[i].eqSpeed()-I)/2; // norme de (dX;dY) pour cette itération
    
    // ============ Détermination de la zone de conscience =============
    
    double zone_xmin = 0;
    double zone_ymin = 0;
    double zone_xmax = 0;
    double zone_ymax = 0;
    
    //Renvoie les coordonnées de la zone dans laquelle est ce piéton
    double xmax = width_+2.5; //si les piétons sortent du batiment, ils voient plus loin que le mur
    double xmin = -2.5;
    for (unsigned int i=0; i<xborders_.size(); i++){
      double xlim = xborders_[i];
      if (xlim>xmin and xlim<x) xmin = xlim; //xmin plus grande frontière inférieure à x
      if (xlim<xmax and xlim>x) xmax = xlim; //xmax plus petite frontière supérieure à x
    }
    double ymax = length_+2.5;
    double ymin = -2.5;
    for (unsigned int i=0; i<yborders_.size(); i++){
      double ylim = yborders_[i];
      if (ylim>ymin and ylim<y) ymin = ylim;
      if (ylim<ymax and ylim>y) ymax = ylim;
    }
    
    //Renvoie les coordonnées des murs qui encadrent ce piéton
    double w_xmax = width_+2.5; //si les piétons sortent du batiment, ils voient plus loin que le mur
    double w_xmin = -2.5;
    for (unsigned int i=0; i<xborders_.size(); i++){
      double xlim = xborders_[i];
      if (map_[width_*((int) y)+((int) xlim)]==0) continue; // si pas de mur à la hauteur du piéton cette limite compte pas
      if (xlim>w_xmin and xlim<x) w_xmin = xlim; //xmin plus grande frontière inférieure à x
      if (xlim<w_xmax and xlim>x) w_xmax = xlim; //xmax plus petite frontière supérieure à x
    }
    double w_ymax = length_+2.5;
    double w_ymin = -2.5;
    for (unsigned int i=0; i<yborders_.size(); i++){
      double ylim = yborders_[i];
      if (map_[width_*((int) ylim)+((int) x)]==0) continue;
      if (ylim>w_ymin and ylim<y) w_ymin = ylim;
      if (ylim<w_ymax and ylim>y) w_ymax = ylim;
    }
    
    switch (main_dir){
      //la zone à scanner est entre toi et le prochain mur dans la 
      //direction ou tu vas      
      case 0: 
        zone_ymax = y;
        zone_ymin = w_ymin+0.5;
        zone_xmin = x - r/Building::ZOOM - float(Pedest::RMAX)/Building::ZOOM;
        zone_xmax = x + r/Building::ZOOM + float(Pedest::RMAX)/Building::ZOOM;
        break;
      case 1:
        zone_xmin = x;
        zone_xmax = w_xmax;
        zone_ymin = y - r/Building::ZOOM - float(Pedest::RMAX)/Building::ZOOM;
        zone_ymax = y + r/Building::ZOOM + float(Pedest::RMAX)/Building::ZOOM;
        break;
      case 2:
        zone_ymin = y;
        zone_ymax = w_ymax;
        zone_xmin = x - r/Building::ZOOM - float(Pedest::RMAX)/Building::ZOOM;
        zone_xmax = x + r/Building::ZOOM + float(Pedest::RMAX)/Building::ZOOM;
        break;
      case 3:
        zone_xmax = x;
        zone_xmin = w_xmin+0.5;
        zone_ymin = y - r/Building::ZOOM - float(Pedest::RMAX)/Building::ZOOM;
        zone_ymax = y + r/Building::ZOOM + float(Pedest::RMAX)/Building::ZOOM;
    }
    
    double space = (zone_xmax-zone_xmin-I)*Building::ZOOM - r;
    space *= (zone_ymax-zone_ymin-I)*Building::ZOOM - r;
    if (space < 0) I = 0;
    
    // Détection de murs dans la zone scannée
    unsigned int walls_dir = 9;
    if (main_dir!= 2 and ymax-0.5 < zone_ymax+0.1) { walls_dir = 0; } //remonte
    if (main_dir!= 0 and walls_dir == 9 and ymin > zone_ymin-0.1) { walls_dir = 2; } //redescends
    if (main_dir!= 1 and walls_dir == 9 and xmax < zone_xmax+0.1) { walls_dir = 3; } //à gauche
    if (main_dir!= 3 and walls_dir == 9 and xmin > zone_xmin-0.1) { walls_dir = 1; } //à droite
    
    //Affiche la zone scannée à l'écran
    Pedest::ZONE_XMIN = zone_xmin;
    Pedest::ZONE_XMAX = zone_xmax;
    Pedest::ZONE_YMIN = zone_ymin;
    Pedest::ZONE_YMAX = zone_ymax;
    
    
    // renvoie la liste des piétons dans la zone scannée
    double x_col = 0;
    double y_col = 0;
    
    vector<Pedest> obstacles;
    for (int i=0; i<Building::NPEDEST; i++){
      double x = people_[i].x();
      double y = people_[i].y();
      if (zone_xmin<x and x<zone_xmax and zone_ymin<y and y<zone_ymax){
        obstacles.push_back(people_[i]);
      }
    }
    
    // ========= plusieurs modèles d'adaptation aux piétons ============
    if ( obstacles.size() ){
      double dmin = 2*I;
      Pedest* nearest;
      switch(Pedest::MODEL){
        case 1:  //On freine et on attend derrière l'obstacle
          for (unsigned int i=0; i<obstacles.size(); i++){
            double distance = sqrt( pow(x-obstacles[i].x(),2) + pow(y-obstacles[i].y(),2) );
            distance -= (r + obstacles[i].radius())/ (double) Building::ZOOM;
            if (distance < I ){
              I = distance;
              if (I<0) I=0;
            }
          }
          break;
          
        case 2:  //On se décale de l'obstacle le plus proche
          for (unsigned int i=0; i<obstacles.size(); i++){
            double distance = sqrt(pow(x-obstacles[i].x(),2) + pow(y-obstacles[i].y(),2));
            distance -= (r + obstacles[i].radius())/ (double) Building::ZOOM;
            if (distance<dmin){
              dmin = distance;
              nearest = &obstacles[i];
            }
          }
          break;
          
        case 3:  //On compte les obstacles à gauche et à droite dans la zone pour prendre tout en compte
          break;
      }

      // Se déplace en fonction de la position du plus proche obstacle
      if(dmin<2*I){
        switch (main_dir){
          case 0:
            if (nearest->x()<x) x_col = (double) (rand()) / (double)(RAND_MAX);
            else x_col = -(double) (rand()) / (double)(RAND_MAX);
            y_col = -(double) (rand()) / (double)(RAND_MAX);
            break;
          case 1:
            if (nearest->y()<y) y_col = (double) (rand()) / (double)(RAND_MAX);
            else y_col = -(double) (rand()) / (double)(RAND_MAX);
            x_col = (double) (rand()) / (double)(RAND_MAX);
            break;
          case 2:
            if (nearest->x()<x) x_col = (double) (rand()) / (double)(RAND_MAX);
            else x_col = -(double) (rand()) / (double)(RAND_MAX);
            y_col = (double) (rand()) / (double)(RAND_MAX);
            break;
          case 3:
            if (nearest->y()<y) y_col = (double) (rand()) / (double)(RAND_MAX);
            else y_col = -(double) (rand()) / (double)(RAND_MAX);
            x_col = -(double) (rand()) / (double)(RAND_MAX);
            break;
        }
      }
    }
    
    double random_dir_x = 0;
    double random_dir_y = 0;
    
    // ===================== calcul du mouvement =======================
    
    double x_move, y_move;
    
    // termes de volonté
    x_move =  (main_dir==1)-(main_dir==3) ; 
    y_move =  (main_dir==2)-(main_dir==0) ;
    
    // terme d'évitement des murs
    x_move += ((walls_dir==1)-(walls_dir==3))*0.9;
    y_move += ((walls_dir==2)-(walls_dir==0))*0.9;
    
    // terme d'évitement des piétons
    x_move +=  x_col;
    y_move +=  y_col;
    
    // terme aléatoire
    x_move +=  random_dir_x;
    y_move +=  random_dir_y;
    
    double hypothenuse = sqrt( pow(x_move,2) + pow(y_move,2) );
    double x_final = x_move*I/hypothenuse;
    double y_final = y_move*I/hypothenuse;
    
    people_[i].move( x_final , y_final , I, Building::ZOOM);
  }
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
  cout << "======= Directions à prendre: =======" << endl << endl;
  for(int j=0; j<l; j++){
    for(int i=0; i<w; i++){
      if (map[i+w*j]==0) cout << "↑" << ' ';
      if (map[i+w*j]==1) cout << "→" << ' ';
      if (map[i+w*j]==2) cout << "↓" << ' ';
      if (map[i+w*j]==3) cout << "←" << ' ';
    }   
    cout << endl;
  }
  cout << endl;
}

void Building::drawMap(int* map, int w, int l) const {
  cout << endl;
  for(int j=0; j<l; j++){
    for(int i=0; i<w; i++){
      char pixel = ' ';
      if (map[ i+w*j] ==1 ) {pixel = '#';}
      cout << pixel << " ";
    }   
    cout << endl;
  }
  cout << endl;
}
