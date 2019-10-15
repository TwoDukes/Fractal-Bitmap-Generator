#pragma once

#include <vector>
#include <utility>
#include "Zoom.h"

namespace Fractal{

class ZoomList {
private:
 int m_width{0};
 int m_height{0};
 std::vector<Zoom> zooms;

public:
    ZoomList(int width, int height);
    void add(const Zoom& zoom);
    std::pair<double,double> doZoom(int x, int y);
};

}