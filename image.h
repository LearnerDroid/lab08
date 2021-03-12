#ifndef IMAGE_H
#define IMAGE_H

#include <math.h>
#include "color.h"

using namespace std;

//difference between class and typename: https://stackoverflow.com/questions/2023977/difference-of-keywords-typename-and-class-in-templates
template <class T>
class image {

	public:
		image(int w, int h, T backGround) : width(w), height(h) {
			for(int i=0; i <width*height; i++)
				thePixels.push_back(backGround);
		}

		int w() const {return width; }
		int h() const {return height; }
	    void writePixel(ostream& out, int x, int y, T cOut) const;
	    void writeHeader(ostream& out) const;
	    void writeNewLine(ostream& out) const;
	    void setPixel(int x, int y, T& in) {
	    	thePixels.at(mapXY(x,y)) = in;
	    }
	    void fullWriteOut(ostream& out) {

			writeHeader(out);
			//for each pixel, write out its color
			for (int y = 0; y < height; y++) {
				for (int x = 0; x < width; x++) {
					writePixel(out, x, y, thePixels.at(mapXY(x, y)));
				}
				writeNewLine(out);
			}
		}

	private:
		int mapXY(int x, int y) {return y*(width-1) + x; }
		int width;
		int height;
		vector<T> thePixels; //cannot have a template class here?
};
/*
void image<T>::fullWriteOut(ostream& out) {

	writeHeader(out);
	//for each pixel, write out its color
	for (int y=0; y < height; y++) {
		for (int x =0; x < width; x++) {
			writePixel(out, x, y, thePixels.at(mapXY(x, y)));
		}
		writeNewLine(out);
	}
}
*/

template<>
void image<color>::writePixel(ostream& out, int x, int y, color cOut) const {
	out << static_cast<int>(clamp(cOut.r(), 0.0, 255)) << " "
		<< static_cast<int>(clamp(cOut.g(), 0.0, 255)) << " "
		<< static_cast<int>(clamp(cOut.b(), 0.0, 255)) << endl;
}
template<>
void image<int>::writePixel(ostream& out, int x, int y, int cOut) const {
	out << cOut << endl;
}
template<>
void image<char>::writePixel(ostream& out, int x, int y, char cOut) const {
	out << cOut << endl;
}
template<>
void image<bool>::writePixel(ostream& out, int x, int y, bool cOut) const {
	out << cOut << endl;
}

template <class T>
void image<T>::writeNewLine(ostream& out) const {
 	out << "\n"; 
}

template<>
void image<color>::writeHeader(ostream& out) const {
	//PPM format header
 	out << "P3\n" << width << " " << height << "\n255\n"; 
}
template<>
void image<int>::writeHeader(ostream& out) const {
	//PGM format header
	out << "P2\n" << width << " " << height << "\n255\n";
}
template<>
void image<char>::writeHeader(ostream& out) const {
	//out << "P3\n" << width << " " << height << "\n255\n";
}
template<>
void image<bool>::writeHeader(ostream& out) const {
	//PBM format header
	out << "P1\n" << width << " " << height << "\n";
}

#endif


