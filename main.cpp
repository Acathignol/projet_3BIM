
#include "Image.h"
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
  unsigned int N = 40; // nombre de piétons à créer
  
  Pedest* people = new Pedest[N];
  for (unsigned int i=0; i<N; i++){
    unsigned int posX = rand()%Bataclan.width();
    unsigned int posY = rand()%Bataclan.length();
    while (Bataclan.map(posX, posY)){
      posX = rand()%Bataclan.width();
      posY = rand()%Bataclan.length();
    }
    unsigned int radius = 5;
    people[i] = Pedest(posX, posY, radius, Bataclan.map(), Bataclan.width(), Bataclan.length() );
  }

  // ==================== Affichage de Copymap =========================
  std::vector<int> edges=Bataclan.vectorEdges();
  for (int i =0 ; i< int(edges.size()); i++){
	  cout<<edges[i]<<endl;
	  for (int x=0; x<Bataclan.width(); x++){
        for (int y=0; y<Bataclan.length(); y++){
		  if (edges[i]==x+y*Bataclan.width()){cout<<"x="<<x<<" y="<<y<<endl;}
		}
	  }
  }
  cout<<"number of edges: "<<int(edges.size())<<endl;
// =============================================================


  cout << N << " pedestrians randomly placed in this floor." << endl;
  
  cout << "\nPath to the exit from (" << people[0].x() << ',' << people[0].y() << ") :\n";
  Bataclan.drawTrajectory( people[0].pathToExit() );
  
  // =================== Affichage du Batiment =========================
  
  RenderWindow fen1(VideoMode(10*Bataclan.width() , 10*Bataclan.length()), "Projet 3BIM", Style::Titlebar | Style::Close);
  fen1.setVerticalSyncEnabled(true);
  vector<RectangleShape> walls_ = Bataclan.walls();
       
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
      for (unsigned int i=0; i<walls_.size(); i++){
        fen1.draw(walls_[i]);
      }
      fen1.draw(people[i].img());
    }
    fen1.display();
  }
  delete[] people;
    
  return EXIT_SUCCESS;
}
