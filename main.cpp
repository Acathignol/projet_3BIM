
#include "Image.h"
#include "Pedest.h"
#include "Building.h"
#include "Point.h"

using namespace std;

int main(int argc, char* argv[]){
  
  // ==================== Import de la Carte ===========================
  
  string filename = "little-room.ppm";
  if (argc > 1) {
    filename = argv[1];
    cout << "using custom building..." << endl;
  }
  
  Image Level(filename);
  Building Bataclan(Level);
  
  cout << filename << " successfully loaded:" << endl;
  cout << "Height: " << Level.height() << endl;
  cout << "Width: " << Level.width() << endl;
  
  // =================== Affichage du Batiment =========================
  
  Bataclan.drawMap();
  
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
  // =================== Création d'un piéton ==========================
  
  Pedest pieton1 = Pedest(1,1,1,Bataclan.map(), Bataclan.width(), 
                          Bataclan.length() );
  cout << "\nPath to the exit from " << pieton1.x() << ',' << pieton1.y() << " :\n";
  Bataclan.drawTrajectory( pieton1.pathToExit() );
    
  return EXIT_SUCCESS;
}
