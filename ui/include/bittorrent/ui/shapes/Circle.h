#pragma once

#include "bittorrent/ui/config.h"

#include "bittorrent/ui/shapes/Arc.h"

namespace bittorrent {
namespace ui {

class Shader;

namespace shapes {

class Circle {
public:
	Circle(double x, double y, double r)
		: x(x), y(y), r(r) {}

	void draw(Shader* shader) {
		Arc(x, y, r, 0.0, 2.0 * M_PI).draw(shader);
	}

	double x, y, r;
};

}}}