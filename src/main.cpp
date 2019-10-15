#include <iostream>
#include <cstdint>
#include <memory>
#include <math.h>
#include "Bitmap.h"
#include "Mandelbrot.h"
#include "ZoomList.h"

using namespace std;
using namespace Bitmapping;
using namespace Fractal;

int main() {

  const int WIDTH = 800;
  const int HEIGHT = 600;

  Bitmap bitmap(WIDTH, HEIGHT);

  ZoomList zoomList(WIDTH, HEIGHT);

  zoomList.add(Zoom(WIDTH/2, HEIGHT/2, 4.0/WIDTH));
  zoomList.add(Zoom(295, HEIGHT-202, 0.1));
  zoomList.add(Zoom(312, HEIGHT-304, 0.1));

  unique_ptr<int[]> histogram(new int[Mandelbrot::MAX_ITERATIONS]{0});
  unique_ptr<int[]> fractal(new int[WIDTH*HEIGHT]{0});

  // Generates Fractal and Pixel Historgrams
  for(int y = 0; y < HEIGHT; y++){
    for(int x = 0; x < WIDTH; x++){
      std::pair<double, double> coords = zoomList.doZoom(x, y);

      int iterations = Mandelbrot::getIterations(coords.first, coords.second);

      fractal[y*WIDTH+x] = iterations;

      if(iterations != Mandelbrot::MAX_ITERATIONS){
        histogram[iterations]++;
      }
    }
  }

  // Write Fractal to Bitmap
  int total = 0;
  for(int i = 0;i < Mandelbrot::MAX_ITERATIONS; i++){
    total += histogram[i];
  }

  for(int y = 0; y < HEIGHT; y++){
    for(int x = 0; x < WIDTH; x++){

      uint8_t red = 0;
      uint8_t green = 0;
      uint8_t blue = 0;

      int iterations = fractal[y * WIDTH + x];

      if(iterations != Mandelbrot::MAX_ITERATIONS){

        double hue = 0.0; // 0.0 - 1.0

        for(int j = 0; j <= iterations; j++){
          hue += (double)(histogram[j])/total;
        }

        red = 0;
        green = pow(255,hue);
        blue = 0;
      }

      bitmap.setPixel(x, y, red, green, blue);

    }
  }
  

  bitmap.write("test.bmp");

  cout << "Finished" << endl;
  return 0;
}