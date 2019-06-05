#ifndef CONPOINT_H
#define CONPOINT_H

#include <cstdint>

class ConPoint {
	public:
		ConPoint() :
		    _x(0),
		    _y(0) {}
		ConPoint(const uint32_t x, const uint32_t y) :
		    _x(x),
		    _y(y) {}
		uint32_t x() const {
			return _x;
		}
		uint32_t y() const {
			return _y;
		}
	private:
		uint32_t _x;
		uint32_t _y;
};

#endif // CONPOINT_H
