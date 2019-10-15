#include <iostream>

#include "FractalCreator.h"
#include "RGB.h"
#include "Zoom.h"

using namespace Fractal;

int main() {

  FractalCreator fractalCreator(800, 600);
  fractalCreator.addZoom(Zoom(295, 202, 0.1));
  fractalCreator.addZoom(Zoom(312, 304, 0.1));
  fractalCreator.run("test.bmp");

  cout << "Finished" << endl;
  return 0;
}