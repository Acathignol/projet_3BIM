
#include "Image.h"
#include "Pedest.h"

using namespace std;

int main(int argc, char* argv[]){
  Pedest pieton1 = Pedest(2,2);
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
