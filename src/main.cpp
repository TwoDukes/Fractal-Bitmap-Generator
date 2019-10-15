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

  unique_ptr<int[]> histogram(new int[Mandelbrot::MAX_ITERATIONS]{0});
  unique_ptr<int[]> fractal(new int[WIDTH*HEIGHT]{0});

  // Generates Fractal and Pixel Historgrams
  for(int y = 0; y < HEIGHT; y++){
    for(int x = 0; x < WIDTH; x++){
      double xFractal = (x - WIDTH/2 - 200) * 2.0/HEIGHT;
      double yFractal = (y - HEIGHT/2) * 2.0/HEIGHT;

      int iterations = Mandelbrot::getIterations(xFractal, yFractal);

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