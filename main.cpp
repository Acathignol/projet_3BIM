
#include "Image.h"
#include "Pedest.h"
#include "Building.h"

using namespace std;

int main(int argc, char* argv[]){
  
  string filename = "batiment.ppm";
  if (argc > 1) {
    filename = argv[1];
    cout << "using custom building..." << endl;
  }
  
  Image Level(filename);
  cout << filename << " successfully loaded:" << endl;
  cout << "Height: " << Level.height() << endl;
  cout << "Width: " << Level.width() << endl;
  
  Pedest pieton1 = Pedest(2,2,1);
  
  for(int i=1; i<10; i++){
    cout << "X:" << pieton1.x() << ",Y:" << pieton1.y() << endl;
    pieton1.move();
    if (double(i/2) == double(i)/2) {
      pieton1.accelerate();
      cout << "Accélération !\n";
    }
  }
  
  return EXIT_SUCCESS;
}
