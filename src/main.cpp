#include <iostream>
#include "Bitmap.h"

using namespace std;
using namespace Bitmapping;

int main() {


  Bitmap bitmap(800, 600);

  bitmap.write("test.bmp");

  cout << "Finished" << endl;
  return 0;
}