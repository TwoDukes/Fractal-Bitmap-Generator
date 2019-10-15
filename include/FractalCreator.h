#pragma once

#include <string>
#include <cstdint>
#include <memory>
#include <math.h>

#include "Bitmap.h"
#include "Mandelbrot.h"
#include "ZoomList.h"
#include "RGB.h"

namespace Fractal{

class FractalCreator {
private:
  int m_width;
  int m_height;

  std::unique_ptr<int[]> m_histogram;
  std::unique_ptr<int[]> m_fractal;

  Bitmapping::Bitmap m_bitmap;

  ZoomList m_zoomList;

  int m_totalIterations{0};

private:
  void calculateIndividualIterations();
  void cacluateTotalIterations();
  void drawFractal();
  void writeBitmap(std::string name);

public:
  FractalCreator(int width, int height);
  virtual ~FractalCreator();
  
  void addZoom(const Zoom &zoom);
  void run(std::string name);
};

}