#include "FractalCreator.h"

namespace Fractal{


void FractalCreator::addRange(double rangeEnd, const RGB &rbg){
  m_ranges.push_back(rangeEnd * Mandelbrot::MAX_ITERATIONS);
  m_colors.push_back(rbg);

  if(m_bGotFirstRange){
    m_rangeTotals.push_back(0);
  }

  m_bGotFirstRange = true;
}

void FractalCreator::addZoom(const Zoom &zoom){
  m_zoomList.add(zoom);
}

void FractalCreator::run(std::string name){
  calculateIndividualIterations();
  calcuateTotalIterations();
  calculateRangeTotals();
  drawFractal();
  writeBitmap(name);
}

FractalCreator::FractalCreator(int width, int height):m_width(width),
                                                      m_height(height),
                                                      m_histogram(new int[Mandelbrot::MAX_ITERATIONS]{0}),
                                                      m_fractal(new int[width*height]{0}),
                                                      m_bitmap(width, height),
                                                      m_zoomList(width, height)
{
    // Start of constructor method                                                   
    m_zoomList.add(Zoom(m_width/2, m_height/2, 4.0/m_width));
}

FractalCreator::~FractalCreator() {

}

// Generates Fractal and Pixel Historgrams
void FractalCreator::calculateIndividualIterations(){
  for(int y = 0; y < m_height; y++){
    for(int x = 0; x < m_width; x++){
      std::pair<double, double> coords = m_zoomList.doZoom(x, y);

      int iterations = Mandelbrot::getIterations(coords.first, coords.second);

      m_fractal[y*m_width+x] = iterations;

      if(iterations != Mandelbrot::MAX_ITERATIONS){
        m_histogram[iterations]++;
      }
    }
  }
}

void FractalCreator::calcuateTotalIterations(){
  
  for(int i = 0;i < Mandelbrot::MAX_ITERATIONS; i++){
    m_totalIterations += m_histogram[i];
  }
}

void FractalCreator::calculateRangeTotals(){

  int rangeIndex = 0;

  for(int i = 0; i < Mandelbrot::MAX_ITERATIONS; i++){
    int pixels = m_histogram[i];

    if(i >= m_ranges[rangeIndex+1]){
      rangeIndex++;
    }

    m_rangeTotals[rangeIndex] += pixels;
  }
}

int FractalCreator::getRange(int iterations) const {
  int range = 0;

  for(uint32_t i = 1; i < m_ranges.size(); i++){
    range = i;

    if(m_ranges[i] > iterations){
      break;
    }
  }

  range--;

  assert(range > -1);
  assert(range < m_ranges.size());

  return range;
}

// Set Pixel colors of Fractal in Bitmap
void FractalCreator::drawFractal(){

  for(int y = 0; y < m_height; y++){
    for(int x = 0; x < m_width; x++){

      int iterations = m_fractal[y * m_width + x];

      int range = getRange(iterations);
      int rangeTotal = m_rangeTotals[range];
      int rangeStart = m_ranges[range];

      RGB &startColor = m_colors[range];
      RGB &endColor = m_colors[range + 1];
      RGB colorDif = endColor - startColor;


      uint8_t red = 0;
      uint8_t green = 0;
      uint8_t blue = 0;

      if(iterations != Mandelbrot::MAX_ITERATIONS){

        int totalPixels = 0;

        for(int j = rangeStart; j <= iterations; j++){
          totalPixels += m_histogram[j];
        }
 
        red = startColor.r + colorDif.r * (double)totalPixels/rangeTotal;
        green = startColor.g + colorDif.g * (double)totalPixels/rangeTotal;
        blue = startColor.b + colorDif.b * (double)totalPixels/rangeTotal;
      }

      m_bitmap.setPixel(x, y, red, green, blue);

    }
  } 
}

void FractalCreator::writeBitmap(std::string name){ 
  m_bitmap.write(name);
}

}