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
  cout << "number of x edges: " << int(Bataclan.xborders().size()) << " ( ";
  for (unsigned int i=0; i<Bataclan.xborders().size(); i++){
    cout << Bataclan.xborders()[i];
    cout << " ";
  }
  cout << ")\nnumber of y edges: " << int(Bataclan.yborders().size()) << " ( ";
  for (unsigned int i=0; i<Bataclan.yborders().size(); i++){
    cout << Bataclan.yborders()[i];
    cout << " ";
  }
  cout << ")\n";
  cout << "Height: " << Bataclan.length() << endl;
  cout << "Width: " << Bataclan.width() << endl;
  cout << Building::Npedest << " pedestrians randomly placed in this floor.\n" << endl;
  
  //~ Bataclan.drawMap();
  //~ cout << "\nPath to the exit from (" << Bataclan.people(0).x() << ',' << Bataclan.people(0).y() << ") :\n";
  //~ Bataclan.drawTrajectory( Bataclan.people(0).pathToExit() );
  
  // =================== Affichage du Batiment =========================
  
  RenderWindow fen1(VideoMode(10*Bataclan.width() , 10*Bataclan.length()), "Projet 3BIM", Style::Titlebar | Style::Close);
  fen1.setVerticalSyncEnabled(true);
  vector<RectangleShape> walls_ = Bataclan.walls();
  
  while (fen1.isOpen()){
    //Gestion des évênements
    Event action;
    while (fen1.pollEvent(action)){
      if (action.type == Event::Closed)
        fen1.close();
    }
    
    //Rafraichissement du dessin
    fen1.clear(Color::Black);
    for (int i=0; i<Building::Npedest; i++){
      for (unsigned int j=0; j<walls_.size(); j++){
        fen1.draw(walls_[j]);
      }
      fen1.draw(Bataclan.people(i).img());
    }
    fen1.display();
  }
  
  return EXIT_SUCCESS;
}
