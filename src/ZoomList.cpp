#include "ZoomList.h"

namespace Fractal{

ZoomList::ZoomList(int width, int height):m_width(width),m_height(height) {

}


void ZoomList::add(const Zoom& zoom){
  zooms.push_back(zoom);
}

std::pair<double,double> ZoomList::doZoom(int x, int y){
  return std::pair<double,double>(0,0);
}

}