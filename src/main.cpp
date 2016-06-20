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
  
  string filename = "bmp/batiment.bmp";
  unsigned int show_graphics = 1;
  
  switch (argc){
    case 1:
    {
      cout << "./escape [ default ] path/to/file.bmp [ Npedest  model LimSpeed  show? ]" << endl;
      cout << "Number of pedestrians to put in: ";
      scanf("%d", &Building::NPEDEST);
      cout << endl;
      cout << "Model type:" << endl;
      cout << "1 = Pedestrians wait behind the obstacles" << endl;
      cout << "2 = Pedestrians move from the nearest obstacle" << endl;
      cout << "3 = Pedestrians move from the average position of obstacles" << endl;
      cout << "Model to use ? : ";
      scanf("%d", &Pedest::MODEL);
      cout << endl;
      float speed = 0;
      cout << "Average limit speed of pedestrians ? (in m/s): ";
      scanf("%f", &speed);
      cout << endl;
      Pedest::EQSPEEDMAX = (int) (10*speed + 2);
      Pedest::EQSPEEDMIN = (int) (10*speed - 2);
      if (Pedest::EQSPEEDMAX<1) Pedest::EQSPEEDMAX=1;
      if (Pedest::EQSPEEDMAX>20) Pedest::EQSPEEDMAX=20;
      if (Pedest::EQSPEEDMIN<1) Pedest::EQSPEEDMIN=1;
      if (Pedest::EQSPEEDMIN>20) Pedest::EQSPEEDMIN=20;
      cout << "Show the simulation? (0=Non, 1=Oui): ";
      scanf("%d", &show_graphics);
      cout << endl;
      break;
    }
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
      
    case 6:
    {
      filename = argv[1];
      cout << "using custom parameters..." << endl;
      cout << "using custom building..." << endl;
      Building::NPEDEST = atoi(argv[2]);
      Pedest::MODEL = atoi(argv[3]);
      float speed = atof(argv[4]);
      Pedest::EQSPEEDMAX = (int) (10*speed + 2);
      Pedest::EQSPEEDMIN = (int) (10*speed - 2);
      if (Pedest::EQSPEEDMAX<1) Pedest::EQSPEEDMAX=1;
      if (Pedest::EQSPEEDMAX>20) Pedest::EQSPEEDMAX=20;
      if (Pedest::EQSPEEDMIN<1) Pedest::EQSPEEDMIN=1;
      if (Pedest::EQSPEEDMIN>20) Pedest::EQSPEEDMIN=20;
      show_graphics = atoi(argv[5]);
    }
  }
  if (argc>=3 and argc!=6){
    cout << "./escape [ default ] path/to/file.bmp [ Npedest  model  LimSpeed  show? ]" << endl;
    exit(-1);
  }

  Building Bataclan(filename);
  
  // =================== Simulation =========================
  
  cout << "=======================================" << endl;
  cout << "Building: " << filename << endl;
  cout << "Number of pedestrians: " << Building::NPEDEST << endl;
  cout << "Average limit speed of pedestrians: " << (Pedest::EQSPEEDMAX-Pedest::EQSPEEDMIN)/20.0 << endl;
  cout << "Model used: ";
  switch (Pedest::MODEL){
   case 1: 
    cout << "Pedestrians wait behind the obstacles" << endl;
    break;
   case 2:
    cout << "Pedestrians move from the nearest obstacle" << endl;
    break;
   case 3:
    cout << "Pedestrians move from the average position of obstacles" << endl;
  }
  if (not show_graphics) cout << "Data files saved to results/ folder." << endl;
  cout << "=======================================" << endl;
  
  
  unsigned int time = 0; // en secondes
  int success = EXIT_SUCCESS;
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
        break;
      }
    case 0:
      {
        //~ success += system("if [ -f speed.txt]; then rm speed.txt; fi");
        //~ success += system("if [ -f exit-time.txt]; then rm exit-time.txt; fi");
        success += system("if [ -f density-at-0000.ppm ]; then rm *.ppm; fi");
        success += system("if [ -d 'results' ]; then rm results/speed.txt results/exit-time.txt results/density.gif; else mkdir results; fi");
        while (Bataclan.notEmpty()){
          Bataclan.movePeople();
          Bataclan.studyPeople(time);
          time ++;
        }
        success += system("mv speed.txt results/speed.txt");
        success += system("mv exit-time.txt results/exit-time.txt");
        cout << "creating .gif..." << endl;
        success += system("convert -delay 5 -loop 0 density-at-*.ppm density.gif");
        success += system("mv density.gif results/density.gif");
        success += system("rm *.ppm");
      }
  }
  cout << "\nEverybody found an exit in " << time-1 << " seconds !" << endl;
  return EXIT_SUCCESS;
}
