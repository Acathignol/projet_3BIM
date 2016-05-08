#include "Pedest.h"
#include "Building.h"
#include <ctime>

using namespace std;
using namespace sf;

int main(int argc, char* argv[]){
  
  srand(time(NULL));
  
  // ==================== Import de la Carte ===========================
  
  string filename = "little-room.bmp";
  if (argc > 1) {
    filename = argv[1];
    cout << "using custom building..." << endl;
  }

  Building Bataclan(filename);
  
  cout << filename << " successfully loaded:" << endl;
  cout << "Height: " << Bataclan.length() << endl;
  cout << "Width: " << Bataclan.width() << endl;
  
  //~ Bataclan.drawMap();
  
  // =================== Création des piétons ==========================
  unsigned int N = 1; // nombre de piétons à créer
  
  Pedest* people = new Pedest[N];
  for (unsigned int i=0; i<N; i++){
    unsigned int posX = rand()%Bataclan.width();
    unsigned int posY = rand()%Bataclan.length();
    unsigned int radius = 5;
    people[i] = Pedest(posX, posY, radius, Bataclan.map(), Bataclan.width(), Bataclan.length() );
  }
  cout << N << " pedestrians randomly placed in this floor." << endl;
  
  cout << "\nPath to the exit from " << people[0].x() << ',' << people[0].y() << " :\n";
  Bataclan.drawTrajectory( people[0].pathToExit() );
  
  // =================== Affichage du Batiment =========================
  
  RenderWindow fen1(VideoMode(10*Bataclan.width() , 10*Bataclan.length()), "Projet 3BIM", Style::Titlebar | Style::Close);
  fen1.setVerticalSyncEnabled(true);
  
  while (fen1.isOpen()){
    //======================= Gestion des évênements ===================
    Event action;
    while (fen1.pollEvent(action)){
      if (action.type == Event::Closed)
        fen1.close();
    }
    
    //======================= Rafraichissement du dessin ===============
    fen1.clear(Color::Black);
    for (unsigned int i=0; i<N; i++){
      fen1.draw(people[i].img());
    }
    fen1.display();
  }
  delete[] people;
    
  return EXIT_SUCCESS;
}
