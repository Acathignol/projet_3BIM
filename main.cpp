#include "Building.h"
#include <ctime>

using namespace std;
using namespace sf;


void update_graphics( RenderWindow& fen1, Building& Bataclan, vector<RectangleShape>& walls_ ){
  //Rafraichissement du dessin
  fen1.clear(Color::Black);
  RectangleShape awareness(Vector2f((Pedest::ZONE_XMAX-Pedest::ZONE_XMIN)*Building::ZOOM , (Pedest::ZONE_YMAX-Pedest::ZONE_YMIN)*Building::ZOOM));
  awareness.setPosition(Pedest::ZONE_XMIN*Building::ZOOM, Pedest::ZONE_YMIN*Building::ZOOM);
  awareness.setOutlineThickness(1);
  awareness.setFillColor(Color::Black);
  awareness.setOutlineColor(Color::Red);
  
  for (int i=0; i<Bataclan.width(); i++){
    for (int j=0; j<Bataclan.length(); j++){
      RectangleShape wall(Vector2f(Building::ZOOM,Building::ZOOM));
      wall.setPosition(Building::ZOOM*i, Building::ZOOM*j);
      wall.setOutlineThickness(1);
      wall.setFillColor(Color::Black);
      wall.setOutlineColor(Color::Blue);
      fen1.draw(wall);
    }
  }
  fen1.draw(awareness);
  for (unsigned int j=0; j<walls_.size(); j++){
    fen1.draw(walls_[j]);
  }
  for (int i=0; i<Building::NPEDEST; i++){
    fen1.draw(Bataclan.people(i).img());
  }
  fen1.display();
}


int main(int argc, char* argv[]){
  
  srand(time(NULL));
  
  // ==================== Définition des paramêtres ====================
  
  string filename = "batiment.bmp";
  unsigned int show_graphics = 1;
  
  switch (argc){
    case 1:
      cout << "./main [ default ] filename.bmp [ Npedest  model  show? ]" << endl;
      cout << "Nombre de piétons à placer: ";
      scanf("%d", &Building::NPEDEST);
      cout << endl;
      cout << "Type de modèle:" << endl;
      cout << "1 = Les piétons attendent derrière les obstacles" << endl;
      cout << "2 = Les piétons se décalent de l'obstacle le plus proche" << endl;
      cout << "3 = Les piétons se décalent de la moyenne des positions des obstacles" << endl;
      cout << "Modèle à utiliser: ";
      scanf("%d", &Pedest::MODEL);
      cout << endl;
      cout << "Afficher la simulation? (0=Non, 1=Oui): ";
      scanf("%d", &show_graphics);
      cout << endl;
      break;
    
    case 2:
    {
      cout << "using default parameters..." << endl;
      string arg(argv[1]);
      string Default = "default";
      if (arg == Default) break;
      filename = argv[1];
      cout << "using custom building..." << endl;
      break;
    }
      
    case 5:
      filename = argv[1];
      cout << "using custom parameters..." << endl;
      cout << "using custom building..." << endl;
      Building::NPEDEST = atoi(argv[2]);
      Pedest::MODEL = atoi(argv[3]);
      show_graphics = atoi(argv[4]);
    
  }
  if (argc>=3 and argc!=5){
    cout << "./main [ default ] filename.bmp [ Npedest  model  show? ]" << endl;
    exit(-1);
  }

  Building Bataclan(filename);
  
  // =================== Simulation =========================
  
  unsigned int time = 0; // en secondes
  switch (show_graphics){
    case 1:
    {
      RenderWindow fen1(VideoMode(Building::ZOOM*Bataclan.width() , Building::ZOOM*Bataclan.length()), "Projet 3BIM", Style::Titlebar | Style::Close);
      fen1.setVerticalSyncEnabled(true);
      vector<RectangleShape> walls_ = Bataclan.walls();
      update_graphics(fen1, Bataclan, walls_);
      
      clock_t start;
      start = clock();
      while (fen1.isOpen()){
        
        //Gestion des évênements
        Event action;
        while (fen1.pollEvent(action)){
          if (action.type == Event::Closed)
            fen1.close();
        }
        if (not Bataclan.notEmpty()) fen1.close();
        
        if ( (double) (clock()-start)*100/CLOCKS_PER_SEC > 1){ 
          //une itération du calcul = 1/100ème de seconde 
          update_graphics(fen1, Bataclan, walls_);
          Bataclan.movePeople();
          start = clock();
          time ++;
        }
      }
    }
    case 0:
    {
      while (Bataclan.notEmpty()){
        Bataclan.movePeople();
        Bataclan.studyPeople(time);
        time ++;
      }
    }
  }
  cout << "Everybody found an exit in " << time << " seconds !" << endl;
  return EXIT_SUCCESS;
}
