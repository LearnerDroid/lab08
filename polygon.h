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
				vec2 temp = theVerts.back();
				while(theVerts.size() > 2) {
					theVerts.pop_back();
				}
				theVerts.push_back(temp);
				this->setColor(color(255, 0, 0));
				throw "polygon concave";
			}
		}
		catch (const char* e) {
			std::cout << e << std::endl;
		}
		//Test Failed : 'polygon concave\npolygon concave\nellipse divide zero\nrect order incorrect\npolygon vert less zero\nellipse center less zero\nrect vert less zero\nrect order incorrect\nellipse center less zero\nellipse divide zero\npolygon vert less zero\npolygon concave\nwriting an image of size: 300 300 to: out\n'
		//	          'polygon concave\npolygon concave\n                     rect order incorrect\npolygon vert less zero\nellipse center less zero\n                     rect order incorrect\nellipse center less zero\n                     polygon vert less zero\n                 writing an image of size: 300 300 to: out\n
	}
  private:
	std::vector<vec2> theVerts;

};

#endif
