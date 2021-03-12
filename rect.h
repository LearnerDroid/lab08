#ifndef RECT_H
#define RECT_H

#include "vec2.h"
#include "shape.h"

/* simple data representation of a rectangle */
class Rect : public shape {
  public:
	Rect(double lX, double lY, double rX, double rY, color C, double deep) : shape{C, deep},
		upperL(lX, lY), lowerR(rX, rY) {}
	
	Rect(vec2(left), vec2(right), color C, double deep) : shape{C, deep},
		upperL(left), lowerR(right) {}
	Rect(vec2(left), double width, double height, color C, double deep) : shape{C, deep},
		upperL(left), lowerR(left.x()+width,left.y()+height) {}

	bool eval(double x, double y) override {
		if ((x >= upperL.x() && x <= lowerR.x()) && (y >= upperL.y() && y <= lowerR.y())) {
			return true;
		}
		return false;
	}

	void setColor(color col) { inC = color{0, 0, col.b()}; }

	void translate(vec2 offset) {
		upperL += offset;
		lowerR += offset;
	}

	double getWidth() const {return lowerR.x() - upperL.x(); }
	double getHeight() const {return lowerR.y() - upperL.y(); }
	double getArea() const {return (lowerR.x() - upperL.x())*(lowerR.y() - upperL.y());}

	void setLCorner(vec2 inLCor) { upperL = inLCor; }
	void setRCorner(vec2 inRCor) {lowerR = inRCor;}

	void validate() override {
		try {
			if (upperL.x() < 0 || upperL.y() < 0) {
				this->setColor(color(0, 0, 0));
				throw "rect vert less zero";
			}
			if (upperL.x() > lowerR.x() || upperL.y() > lowerR.y()) {
				int temp[4]; //correct upperL.x, upperL.y, lowerL.x, and lowerL.y.
				if (upperL.x() > lowerR.x()) {
					temp[0] = lowerR.x();
					temp[2] = upperL.x();
				}
				else {
					temp[0] = upperL.x();
					temp[2] = lowerR.x();
				}
				if (upperL.y() > lowerR.y()) {
					temp[1] = lowerR.y();
					temp[3] = upperL.y();
				}
				else {
					temp[1] = upperL.y();
					temp[3] = lowerR.y();
				}
				upperL.setX(temp[0]);
				upperL.setY(temp[1]);
				lowerR.setX(temp[2]);
				lowerR.setY(temp[3]);
				this->setColor(color(255, 0, 0));
				throw "rect order incorrect";
			}
		}
		catch (std::string e) {
			std::cout << e << std::endl;
		}
	}

  private:
	vec2 upperL;
	vec2 lowerR;

};

#endif
