#include <iostream>

#include "conframe.h"
#include "transform.h"

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
	ConFrame frame;
	ConPoint p(frame.xRes()/2, frame.yRes()/2);
	uint32_t c = RGB(0, 200, 0);
	Transform<int> mat({{2, 0, 0},
	                    {0, 2, 0},
	                    {0, 0, 0}});
	frame.line(p, p.x()-100, p.y()-100, c);
	frame.line(p, p.x()+100, p.y()+100, c);
	frame.line(p, p.x()+100, p.y()-100, c);
	frame.line(p, p.x()-100, p.y()+100, c);
	frame.line(p, p.x()-100, p.y()-100, c);

	frame.line(p, p.x()-100, p.y(), c);
	frame.line(p, p.x()+100, p.y(), c);

	frame.line(p, p.x(), p.y()-100, c);
	frame.line(p, p.x(), p.y()+100, c);

}
