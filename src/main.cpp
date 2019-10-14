#include <iostream>
#include "Bitmap.h"

using namespace std;
using namespace Bitmapping;

int main() {

  const int WIDTH = 800;
  const int HEIGHT = 600;

  Bitmap bitmap(WIDTH, HEIGHT);

  for(int i = 0; i < WIDTH; i++){
    for(int j = 0; j < HEIGHT; j++){
      bitmap.setPixel(i, j, 255, 0, 0);
    }
  }

  bitmap.write("test.bmp");

  cout << "Finished" << endl;
  return 0;
}