#include <iostream>

#include "conframe.h"

using namespace std;

struct RGB {
		RGB(uint8_t r=0, uint8_t g=0, uint8_t b=0) :
		    RED(r), GREEN(g), BLUE(b){}
		operator uint32_t() {
			return ((static_cast<uint32_t>(RED) << 16) |
			        (static_cast<uint32_t>(GREEN) << 8) |
			        (static_cast<uint32_t>(BLUE) << 0));
		}
		uint8_t RED;
		uint8_t GREEN;
		uint8_t BLUE;
		const uint8_t packing = 0;
};

int main() {
	try {
		ConFrame frame;
		uint32_t xmid = frame.xRes()/2;
		uint32_t ymid = frame.yRes()/2;
		uint32_t c = RGB(0, 200, 0);
		frame.fill(RGB(200, 0, 200));
		// octant 1.
		frame.line(xmid, ymid, xmid +200, ymid +100, c);
		// octant 2.
		frame.line(xmid, ymid, xmid +100, ymid +200, c);
		// octant 3.
		frame.line(xmid, ymid, xmid -100, ymid +200, c);
		// octant 4.
		frame.line(xmid, ymid, xmid -200, ymid +100, c);
		// octant 5.
		frame.line(xmid, ymid, xmid -200, ymid -100, c);
		// octant 6.
		frame.line(xmid, ymid, xmid -100, ymid -200, c);
		// octant 7.
		frame.line(xmid, ymid, xmid +100, ymid -200, c);
		// octant 8.
		frame.line(xmid, ymid, xmid +200, ymid -100, c);
	}
	catch (const char *str) {
		cout << str << endl;
	}
	while (1);
}
