#include "Building.h"
#include <ctime>

using namespace std;
using namespace sf;

int main(int argc, char* argv[]){
  
  srand(time(NULL));
  
  // ==================== Import de la Carte ===========================
  
  string filename = "batiment.bmp";
  if (argc > 1) {
    filename = argv[1];
    cout << "using custom building..." << endl;
  }

  Building Bataclan(filename);
  
  // =================== Affichage du Batiment =========================
  
  RenderWindow fen1(VideoMode(Building::ZOOM*Bataclan.width() , Building::ZOOM*Bataclan.length()), "Projet 3BIM", Style::Titlebar | Style::Close);
  fen1.setVerticalSyncEnabled(true);
  vector<RectangleShape> walls_ = Bataclan.walls();
  
  while (fen1.isOpen()){
    //Gestion des évênements
    Event action;
    while (fen1.pollEvent(action)){
      if (action.type == Event::Closed)
        fen1.close();
    }
    if (not Bataclan.notEmpty()) fen1.close();
    
    //Rafraichissement du dessin
    fen1.clear(Color::Black);
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
    for (unsigned int j=0; j<walls_.size(); j++){
      fen1.draw(walls_[j]);
    }
    for (int i=0; i<Building::NPEDEST; i++){
      fen1.draw(Bataclan.people(i).img());
    }
    fen1.display();
    
    //Déplacement des piétons
    Bataclan.movePeople();
    
  }
  
  cout << "Everybody found an exit !" << endl;
  return EXIT_SUCCESS;
}
