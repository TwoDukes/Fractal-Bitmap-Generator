#pragma once

namespace Fractal{

class Mandelbrot {
public:
	static const int MAX_ITERATIONS = 2500;

public:
	Mandelbrot();
	virtual ~Mandelbrot();

	static int getIterations(double x, double y);
};

}


