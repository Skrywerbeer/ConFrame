#ifndef CONPOINT_H
#define CONPOINT_H

#include <cstdint>

class ConPoint {
	public:
		ConPoint() :
		    _x(0),
		    _y(0),
		    _z(0) {}
		ConPoint(const uint32_t x, const uint32_t y) :
		    _x(x),
		    _y(y),
		    _z(0) {}
		ConPoint(const uint32_t x, const uint32_t y, const uint32_t z) :
		    _x(x),
		    _y(y),
		    _z(z) {}
		uint32_t x() const {
			return _x;
		}
		uint32_t y() const {
			return _y;
		}
		uint32_t z() const {
			return _z;
		}
	private:
		uint32_t _x;
		uint32_t _y;
		uint32_t _z;
};



#endif // CONPOINT_H
