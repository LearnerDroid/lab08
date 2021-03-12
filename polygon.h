#ifndef POLY_H
#define POLY_H
#include <vector>
#include "vec2.h"
#include "color.h"
#include "shape.h"
#include <algorithm>

/* simple data representation of an implicit ellipse */
class Polygon : public shape {
  public:

	Polygon(vec2 v1, double d, color C) : shape{C,d} {
		theVerts.push_back(v1);
	}

	bool eval(double x, double y) override;
	void addVert(vec2 inV) { theVerts.push_back(inV); }
	bool concave();
	void validate() override {
		try {
			for (vec2 v : theVerts) {
				if (v.x() < 0 || v.y() < 0) {
					this->setColor(color(0, 0, 0));
					throw "polygon vert less zero";
				}
			}
			if (concave()) {
				std::vector<vec2> temp;
				temp.push_back(theVerts.at(0));
				temp.push_back(theVerts.at(1));
				temp.push_back(theVerts.at(theVerts.size()));
				this->setColor(color(255, 0, 0));
				throw "polygon concave";
			}
		}
		catch (std::string e) {
			std::cout << e << std::endl;
		}
	}
  private:
	std::vector<vec2> theVerts;

};

#endif
