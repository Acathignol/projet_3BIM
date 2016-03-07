
#include "Image.h"
#include "Pedest.h"
#include "Building.h"

using namespace std;

int main(int argc, char* argv[]){
  
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
  
  Pedest pieton1 = Pedest(2,2,1);
  
  Bataclan.drawMap();
  for(int i=2; i<12; i++){
    Bataclan.setValue(i,2,2);
  }
  Bataclan.drawMap();
    
  return EXIT_SUCCESS;
}
