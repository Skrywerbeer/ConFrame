#include <iostream>

#include "conframe.h"

using namespace std;

struct RGB {
		RGB(uint8_t r=0, uint8_t g=0, uint8_t b=0) :
		    RED(r), GREEN(g), BLUE(b){}
		operator uint32_t() {
			return ((static_cast<uint32_t>(RED) << 24) |
			        (static_cast<uint32_t>(GREEN) << 16) |
			        (static_cast<uint32_t>(BLUE) << 8));
		}
		uint8_t RED;
		uint8_t GREEN;
		uint8_t BLUE;
		const uint8_t packing = 0;
};

int main() {
	try {
		ConFrame frame;
		for (uint32_t y = 0; y < frame.yRes(); ++y)
			frame.pixel(frame.xRes()/2, y,
			            RGB(20, 100, 20));
		for (uint32_t x = 0; x < frame.xRes(); ++x)
			frame.pixel(x, frame.yRes()/2,
			            RGB(100, 20, 100));

	}
	catch (const char *str) {
		cout << str << endl;
	}
}
