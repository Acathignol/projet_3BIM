
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
  
  // =================== Création d'un piéton ==========================
  
  Pedest pieton1 = Pedest(2,2,1,Bataclan.map(), Bataclan.width(), 
                          Bataclan.length() );
  cout << "\nPath to the exit from " << pieton1.x() << ',' << pieton1.y() << " :\n";
  Bataclan.drawTrajectory( pieton1.pathToExit() );
    
  return EXIT_SUCCESS;
}
