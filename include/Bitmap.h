#pragma once

#include <string>
#include <cstdint>
#include <memory>
using namespace std;

namespace Bitmapping{

class Bitmap {
private:
  int m_width{0};
  int m_height{0};
  unique_ptr<uint8_t[]> m_pPixels;


public:
  Bitmap(int width, int height);
  void setPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue);
  bool write(string filename);
  virtual ~Bitmap();
};

}
