#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <memory>
#include <math.h>
#include <assert.h>

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

  vector<int> m_ranges;
  vector<RGB> m_colors;
  vector<int> m_rangeTotals;

  bool m_bGotFirstRange{false};

private:
  void calculateIndividualIterations();
  void calcuateTotalIterations();
  void calculateRangeTotals();
  void drawFractal();
  void writeBitmap(std::string name);
  int getRange(int iterations) const;

public:
  FractalCreator(int width, int height);
  virtual ~FractalCreator();
  
  void addRange(double rangeEnd, const RGB &rbg);
  void addZoom(const Zoom &zoom);
  void run(std::string name);
};

}