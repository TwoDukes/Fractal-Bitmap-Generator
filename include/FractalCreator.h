#pragma once

#include <string>
#include <cstdint>
#include <memory>
#include <math.h>

#include "Bitmap.h"
#include "Mandelbrot.h"
#include "ZoomList.h"

namespace Fractal{

class FractalCreator {
private:
  int m_width;
  int m_height;

  std::unique_ptr<int[]> m_histogram;
  std::unique_ptr<int[]> m_fractal;

  Bitmapping::Bitmap m_bitmap;

  ZoomList m_zoomList;

  int m_total{0};

public:
  FractalCreator(int width, int height);
  virtual ~FractalCreator();

  void calculateIterations();
  void cacluateTotalIterations();
  void drawFractal();
  void addZoom(const Zoom &zoom);
  void writeBitmap(std::string name);
};

}