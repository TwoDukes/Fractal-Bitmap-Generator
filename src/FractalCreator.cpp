#include "FractalCreator.h"

namespace Fractal{

void FractalCreator::run(std::string name){

  addZoom(Zoom(295, m_height-202, 0.1));
  addZoom(Zoom(312, m_height-304, 0.1));
  calculateIndividualIterations();
  cacluateTotalIterations();
  drawFractal();
  writeBitmap(name);
}

FractalCreator::FractalCreator(int width, int height):m_width(width),
                                                      m_height(height),
                                                      m_histogram(new int[Mandelbrot::MAX_ITERATIONS]{0}),
                                                      m_fractal(new int[m_width*m_height]{0}),
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

void FractalCreator::cacluateTotalIterations(){
  
  for(int i = 0;i < Mandelbrot::MAX_ITERATIONS; i++){
    m_totalIterations += m_histogram[i];
  }
}

// Set Pixel colors of Fractal in Bitmap
void FractalCreator::drawFractal(){
  for(int y = 0; y < m_height; y++){
    for(int x = 0; x < m_width; x++){

      uint8_t red = 0;
      uint8_t green = 0;
      uint8_t blue = 0;

      int iterations = m_fractal[y * m_width + x];

      if(iterations != Mandelbrot::MAX_ITERATIONS){

        double hue = 0.0; // 0.0 - 1.0

        for(int j = 0; j <= iterations; j++){
          hue += (double)(m_histogram[j])/m_totalIterations;
        }

        red = 0;
        green = hue * 255;
        blue = 0;
      }

      m_bitmap.setPixel(x, y, red, green, blue);

    }
  } 
}

void FractalCreator::addZoom(const Zoom &zoom){
  m_zoomList.add(zoom);
}

void FractalCreator::writeBitmap(std::string name){ 
  m_bitmap.write(name);
}

}