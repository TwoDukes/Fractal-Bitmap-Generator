#pragma once

#include <string>
#include "Zoom.h"

namespace Fractal{

class FractalCreator {
public:
  FractalCreator(int width, int height);
  virtual ~FractalCreator();

  void calculateIteration();
  void drawFractal();
  void addZoom(const Zoom &zoom);
  void writeBitmap(std::string name);
};

}