#include <iostream>

#include "FractalCreator.h"

using namespace Fractal;

int main() {

  int height = 600;

  FractalCreator fractalCreator(800, 600);

  fractalCreator.addZoom(Zoom(295, height-202, 0.1));
  fractalCreator.addZoom(Zoom(312, height-304, 0.1));
  fractalCreator.calculateIterations();
  fractalCreator.cacluateTotalIterations();
  fractalCreator.drawFractal();

  fractalCreator.writeBitmap("test.bmp");

  cout << "Finished" << endl;
  return 0;
}