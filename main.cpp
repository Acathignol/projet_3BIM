#include "ImagePPM.h"
#include "Pedest.h"
#include "Building.h"
#include <ctime>

using namespace std;
using namespace sf;

int main(int argc, char* argv[]){
  
  // ==================== Import de la Carte ===========================
  
  string filename = "little-room.ppm";
  if (argc > 1) {
    filename = argv[1];
    cout << "using custom building..." << endl;
  }
  
  ImagePPM Level(filename);
  Building Bataclan(Level);
  
  cout << filename << " successfully loaded:" << endl;
  cout << "Height: " << Level.height() << endl;
  cout << "Width: " << Level.width() << endl;
  
  // =================== Création des piétons ==========================
  unsigned int N = 5; // nombre de piétons à créer
  
  Pedest* people = new Pedest[N];
  for (unsigned int i=0; i<N; i++){
    unsigned int posX = rand()%Level.height();
    unsigned int posY = rand()%Level.width();
    unsigned int radius = 5;
    people[i] = Pedest(posX, posY, radius, Bataclan.map(), Bataclan.width(), Bataclan.length() );
  }
  
  cout << "\nPath to the exit from " << people[0].x() << ',' << people[0].y() << " :\n";
  Bataclan.drawTrajectory( people[0].pathToExit() );
  
  // =================== Affichage du Batiment =========================
  
  RenderWindow fen1(VideoMode(10*Level.height() , 10*Level.width()), "Projet 3BIM", Style::Titlebar | Style::Close);
  fen1.setVerticalSyncEnabled(true);
  
  while (fen1.isOpen()){
    //======================= Gestion des évênements ===================
    Event event;
    while (fen1.pollEvent(event)){
      if (event.type == sf::Event::Closed)
        fen1.close();
    }
    
    //======================= Rafraichissement du dessin ===============
    fen1.clear(Color::White);
    for (unsigned int i=0; i<N; i++){
      fen1.draw(people[i].img());
    }
    fen1.display();
  }
  delete[] people;
    
  return EXIT_SUCCESS;
}
